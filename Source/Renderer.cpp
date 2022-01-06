#include "Renderer.h"

#include "Model.h"
#include "DefaultShaderPipline.h"
#include "LightingShaderPipline.h"
#include "FrameBuffer.h"
#include <cmath>

Renderer::Renderer(int width, int height)
{
	//shaderPipeline = std::make_shared<DefaultShaderPipline>();
	shaderPipeline = std::make_shared<LightingShaderPipline>();
	frontBuffer = std::make_shared<FrameBuffer>(width, height);
	backBuffer = std::make_shared<FrameBuffer>(width, height);

	viewPortMatrix = CalculateViewPortMatrix(width, height);
}

Matrix4 Renderer::CalculateProjectionMatrix(float fovy, float aspect, float near, float far)
{
	//这个透视投影矩阵是按view矩阵是右手坐标系计算的，计算出来的projection矩阵是左手坐标系的

	Matrix4 result;

	//t/n的值
	float tanHalf = std::tan(fovy / 2.0f);

	//n/t
	float yScale = 1.0 / tanHalf;

	//aspect是r/t，一除变成n/r
	float xScale = yScale / aspect;
	float farMinusNear = far - near;
	float farAddNear = far + near;

	result[0][0] = xScale;
	result[1][1] = yScale;
	result[2][2] = -farAddNear / farMinusNear;
	result[2][3] = -2.0 * far * near / farMinusNear;
	result[3][2] = -1.0f;

	//不能忘记设置0，我的矩阵默认创建单位矩阵
	result[3][3] = 0.0f;

	return result;
}

Matrix4 Renderer::CalculateViewPortMatrix(int width, int height)
{
	//Setup viewport matrix (ndc space -> screen space)
	Matrix4 vpMat;
	float hwidth = width * 0.5f;
	float hheight = height * 0.5f;
	vpMat[0][0] = hwidth; vpMat[0][1] = 0.0f;    vpMat[0][2] = 0.0f; vpMat[0][3] = hwidth;
	vpMat[1][0] = 0.0f;	  vpMat[1][1] = -hheight; vpMat[1][2] = 0.0f; vpMat[1][3] = hheight;
	vpMat[2][0] = 0.0f;   vpMat[2][1] = 0.0f;    vpMat[2][2] = 1.0f; vpMat[2][3] = 0.0f;
	vpMat[3][0] = 0.0f; vpMat[3][1] = 0.0f; vpMat[3][2] = 0.0f; vpMat[3][3] = 0.0f;
	return vpMat;
}

void Renderer::SetModelMatrix(const Matrix4& value)
{
	shaderPipeline->SetModelMatrix(value);
}

void Renderer::SetProjectionMatrix(const Matrix4& value)
{
	shaderPipeline->SetProjectionMatrix(value);
}

void Renderer::SetViewMatrix(const Matrix4& value)
{
	shaderPipeline->SetViewMatrix(value);
}

void Renderer::Render(Model& modelSource)
{
	std::vector<VertexData> rasterizedPoints;
	rasterizedPoints.reserve(backBuffer->GetWidth() * backBuffer->GetHeight());

	auto& meshes = modelSource.meshs;

	for (auto i = 0; i < meshes.size(); i++)
	{
		auto& vertices = meshes[i].vertices;
		auto& indices = meshes[i].indices;
		auto& texrures = meshes[i].textures;

		shaderPipeline->ClearTextures();
		for (auto k = 0; k < texrures.size(); k++)
		{
			shaderPipeline->UploadTexture(texrures[k]);

			if (texrures[k]->type == "texture_diffuse")
			{
				shaderPipeline->SetDiffuseTexId(k);
			}
			else if (texrures[k]->type == "texture_specular")
			{
				shaderPipeline->SetSpecularTexId(k);
			}
		}

		for (auto j = 0; j < indices.size(); j += 3)
		{

			VertexData vertex[3];

			//从模型中按mesh取出每一个三角面片去处理
			vertex[0].position = vertices[indices[j]].position;
			vertex[0].normal = vertices[indices[j]].normal;
			vertex[0].texCoordinate = vertices[indices[j]].texCoords;

			vertex[1].position = vertices[indices[j + 1]].position;
			vertex[1].normal = vertices[indices[j + 1]].normal;
			vertex[1].texCoordinate = vertices[indices[j + 1]].texCoords;

			vertex[2].position = vertices[indices[j + 2]].position;
			vertex[2].normal = vertices[indices[j + 2]].normal;
			vertex[2].texCoordinate = vertices[indices[j + 2]].texCoords;

			//vertex shader处理阶段
			shaderPipeline->VertexShader(vertex[0]);
			shaderPipeline->VertexShader(vertex[1]);
			shaderPipeline->VertexShader(vertex[2]);

			//齐次空间裁剪
			auto clippedVertices = Clipping(vertex[0], vertex[1], vertex[2]);
			if (clippedVertices.empty())
			{
				continue;
			}

			//透视除法
			for (auto& vert : clippedVertices)
			{
				//光栅化前的透视矫正
				VertexData::PrePerspCorrection(vert);

				//从clip space 转换到 ndc space
				vert.clipPosition /= vert.clipPosition.w;
			}

			for (auto k = 0; k < clippedVertices.size() - 2; ++k)
			{
				//Triangle assembly
				VertexData vert[3] = {
						clippedVertices[0],
						clippedVertices[k + 1],
						clippedVertices[k + 2] };

				//背面剔除
				if (IsTowardBackFace(vert[0].clipPosition, vert[1].clipPosition, vert[2].clipPosition))
				{
					continue;
				}

				//计算屏幕坐标
				auto tempVector = viewPortMatrix * vert[0].clipPosition + Vector4(0.5f);
				vert[0].screenPosition = Vector2i(int(tempVector.x), int(tempVector.y));
				tempVector = viewPortMatrix * vert[1].clipPosition + Vector4(0.5f);
				vert[1].screenPosition = Vector2i(int(tempVector.x), int(tempVector.y));
				tempVector = viewPortMatrix * vert[2].clipPosition + Vector4(0.5f);
				vert[2].screenPosition = Vector2i(int(tempVector.x), int(tempVector.y));

				//光栅化
				shaderPipeline->RasterizeFillEdgeFunction(vert[0], vert[1], vert[2],
					backBuffer->GetWidth(), backBuffer->GetHeight(), rasterizedPoints);


				//fragment shader处理阶段
				for (auto& point : rasterizedPoints)
				{
					if (point.clipPosition.z < backBuffer->ReadDepth(point.screenPosition.x, point.screenPosition.y))
					{
						//光栅化之后的透视矫正
						VertexData::AftPrespCorrection(point);

						Vector4 fragColor;
						shaderPipeline->FragmentShader(point, fragColor);
						backBuffer->WritePixelColor(point.screenPosition.x, point.screenPosition.y, fragColor);
						backBuffer->WriteDepth(point.screenPosition.x, point.screenPosition.y, point.clipPosition.z);
					}
				}

				rasterizedPoints.clear();
			}
		}
	}

	std::swap(backBuffer, frontBuffer);
}

void Renderer::SetShaderPipline(std::shared_ptr<ShaderPipeline>& value)
{
	value->SetModelMatrix(shaderPipeline->GetModelMatrix());
	value->SetViewMatrix(shaderPipeline->GetViewMatrix());
	value->SetProjectionMatrix(shaderPipeline->GetProjectionMatrix());

	shaderPipeline = value;
}

const unsigned char* Renderer::GetRenderedColorBuffer()
{
	return frontBuffer->GetColorBuffer().data();
}

void Renderer::ClearColor(const Vector4& color)
{
	backBuffer->Clear(color);
}

std::vector<VertexData> Renderer::Clipping(const VertexData& v0, const VertexData& v1, const VertexData& v2) const
{
	//齐次裁剪空间坐标满足  -w<=x,y,z<=w, near<= w <= far
	//超过这个范围的三角形直接裁掉。

	if (v0.clipPosition.w < near && v1.clipPosition.w < near && v2.clipPosition.w < near)
	{
		return {};
	}

	if (v0.clipPosition.w > far && v1.clipPosition.w > far && v2.clipPosition.w > far)
	{
		return {};
	}

	if (v0.clipPosition.x > v0.clipPosition.w && v1.clipPosition.x > v1.clipPosition.w && v2.clipPosition.x > v2.clipPosition.w)
	{
		return {};
	}

	if (v0.clipPosition.x < -v0.clipPosition.w && v1.clipPosition.x < -v1.clipPosition.w && v2.clipPosition.x < -v2.clipPosition.w)
	{
		return {};
	}

	if (v0.clipPosition.y > v0.clipPosition.w && v1.clipPosition.y > v1.clipPosition.w && v2.clipPosition.y > v2.clipPosition.w)
	{
		return {};
	}

	if (v0.clipPosition.y < -v0.clipPosition.w && v1.clipPosition.y < -v1.clipPosition.w && v2.clipPosition.y < -v2.clipPosition.w)
	{
		return {};
	}

	if (v0.clipPosition.z > v0.clipPosition.w && v1.clipPosition.z > v1.clipPosition.w && v2.clipPosition.z > v2.clipPosition.w)
	{
		return {};
	}

	if (v0.clipPosition.z < -v0.clipPosition.w && v1.clipPosition.z < -v1.clipPosition.w && v2.clipPosition.z < -v2.clipPosition.w)
	{
		return {};
	}

	return { v0, v1, v2 };
}

bool Renderer::IsTowardBackFace(const Vector4& v0, const Vector4& v1, const Vector4& v2) const
{
	//Back face culling in the ndc space
	Vector3 tmp1 = Vector3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
	Vector3 tmp2 = Vector3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

	//叉乘得到法向量
	Vector3 normal = tmp1.CrossProduct(tmp2).Normalize();
	//glm::vec3 view = glm::normalize(glm::vec3(v1.x - camera->Position.x, v1.y - camera->Position.y, v1.z - camera->Position.z));
	//NDC中观察方向指向+z
	Vector3 view = Vector3(0, 0, 1);
	double result = normal * view;

	if (result > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
