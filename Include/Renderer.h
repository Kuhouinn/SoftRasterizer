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
	//先在齐次裁剪空间使用简单裁剪，后续如果有时间可以换成Sutherland算法。
	std::vector<VertexData> Clipping(const VertexData& v0, const VertexData& v1, const VertexData& v2) const;

private:
	float near = 0.01f;
	float far = 1000.0f;
	ShaderPipeline shaderPipeline;
};

