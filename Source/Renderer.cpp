#include "Renderer.h"
#include <cmath>

Matrix4 Renderer::GetProjectionMatrix(float fovy, float aspect, float near, float far)
{
	//���͸��ͶӰ�����ǰ�view��������������ϵ����ģ����������projection��������������ϵ��

	Matrix4 result;

	//t/n��ֵ
	float tanHalf = std::tan(fovy / 2.0f);

	//n/t
	float yScale = 1.0 / tanHalf;
	
	//aspect��r/t��һ�����n/r
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

void Renderer::SetModelMatrix(const Matrix4& model)
{
	shaderPipeline.SetModelMatrix(model);
}

void Renderer::SetProjectionMatrix(const Matrix4& projectionMatrix)
{
	shaderPipeline.SetProjectionMatrix(projectionMatrix);
}

void Renderer::SetViewMatrix(const Matrix4& view)
{
	shaderPipeline.SetViewMatrix(view);
}

void Renderer::Render()
{

}

std::vector<VertexData> Renderer::Clipping(const VertexData& v0, const VertexData& v1, const VertexData& v2) const
{
	//��βü��ռ���������  -w<=x,y,z<=w, near<= w <= far
	//���������Χ��������ֱ�Ӳõ���

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
