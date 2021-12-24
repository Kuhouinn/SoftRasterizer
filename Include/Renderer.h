#pragma once
#include "Matrix4.h"
#include "VertexData.h"
#include "ShaderPipeline.h"
#include <vector>
class Renderer
{
public:
	static Matrix4 CalculateProjectionMatrix(float fovy, float aspect, float near, float far);

	void SetModelMatrix(const Matrix4& model);

	void SetViewMatrix(const Matrix4& view);

	void SetProjectionMatrix(const Matrix4& projection);

	void Render();

private:
	//������βü��ռ�ʹ�ü򵥲ü������������ʱ����Ի���Sutherland�㷨��
	std::vector<VertexData> Clipping(const VertexData& v0, const VertexData& v1, const VertexData& v2) const;

private:
	float near = 0.01f;
	float far = 1000.0f;
	ShaderPipeline shaderPipeline;
};

