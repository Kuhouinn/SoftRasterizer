#pragma once
#include "Matrix4.h"
#include "VertexData.h"

#include <vector>
#include <memory>

class Model;
class ShaderPipeline;
class LightingShaderPipline;
class DirectionalLight;
class FrameBuffer;

class Renderer
{
public:
	Renderer(int width,int height);

	static Matrix4 CalculateProjectionMatrix(float fovy, float aspect, float near, float far);
	static Matrix4 CalculateViewPortMatrix(int width, int height);

	void SetModelMatrix(const Matrix4& value);

	void SetViewMatrix(const Matrix4& value);

	void SetProjectionMatrix(const Matrix4& value);

	void Render(Model& modelSource);

	void SetShaderPipline(std::shared_ptr<ShaderPipeline>& value);

	void SetDirectionalLight(std::shared_ptr<DirectionalLight> light);

	const unsigned char* GetRenderedColorBuffer();

	void ClearColor(const Vector4& color);

private:
	//先在齐次裁剪空间使用简单裁剪，后续如果有时间可以换成Sutherland算法。
	std::vector<VertexData> Clipping(const VertexData& v0, const VertexData& v1, const VertexData& v2) const;

	bool IsTowardBackFace(const Vector4& v0, const Vector4& v1, const Vector4& v2) const;
	bool IsBackFacing(const Vector2i& v0, const Vector2i& v1, const Vector2i& v2) const;

private:
	float near = 0.01f;
	float far = 1000.0f;
	std::shared_ptr<ShaderPipeline> shaderPipeline = nullptr;
	std::shared_ptr<LightingShaderPipline> lightShaderPipeline = nullptr;
	std::shared_ptr<FrameBuffer> frontBuffer = nullptr;
	std::shared_ptr<FrameBuffer> backBuffer = nullptr;

	Matrix4 viewPortMatrix;
};

