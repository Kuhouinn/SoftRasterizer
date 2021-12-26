#pragma once
#include "Matrix4.h"
#include "VertexData.h"

#include <vector>
#include <memory>

class Model;
class ShaderPipeline;
class FrameBuffer;

class Renderer
{
public:
	Renderer();

	static Matrix4 CalculateProjectionMatrix(float fovy, float aspect, float near, float far);

	void SetModelMatrix(const Matrix4& value);

	void SetViewMatrix(const Matrix4& value);

	void SetProjectionMatrix(const Matrix4& value);

	void Render(Model& modelSource);

	void SetShaderPipline(std::shared_ptr<ShaderPipeline>& value);

private:
	//先在齐次裁剪空间使用简单裁剪，后续如果有时间可以换成Sutherland算法。
	std::vector<VertexData> Clipping(const VertexData& v0, const VertexData& v1, const VertexData& v2) const;

private:
	float near = 0.01f;
	float far = 1000.0f;
	std::shared_ptr<ShaderPipeline> shaderPipeline = nullptr;
	std::shared_ptr<FrameBuffer> frontBuffer = nullptr;
	std::shared_ptr<FrameBuffer> backBuffer = nullptr;
};

