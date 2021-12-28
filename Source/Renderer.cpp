#include "Renderer.h"

#include "Model.h"
#include "DefaultShaderPipline.h"
#include "FrameBuffer.h"
#include <cmath>

Renderer::Renderer()
{
	shaderPipeline = std::make_shared<DefaultShaderPipline>();
	frontBuffer = std::make_shared<FrameBuffer>();
	backBuffer = std::make_shared<FrameBuffer>();
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
	result[2][3] = -1;
	result[3][2] = -2.0 * far * near / farAddNear;

	return result;
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
			for (auto& vertex : clippedVertices)
			{
				//光栅化前的透视矫正
				VertexData::PrePerspCorrection(vertex);

				//从clip space 转换到 ndc space
				vertex.clipPosition /= vertex.clipPosition.w;
			}

			//光栅化

			//fragment shader处理阶段
		}

	}
}

void Renderer::SetShaderPipline(std::shared_ptr<ShaderPipeline>& value)
{
	value->SetModelMatrix(shaderPipeline->GetModelMatrix());
	value->SetViewMatrix(shaderPipeline->GetViewMatrix());
	value->SetProjectionMatrix(shaderPipeline->GetProjectionMatrix());

	shaderPipeline = value;
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
