#pragma once
#include <vector>

#include "Matrix4.h"

struct VertexData;

class ShaderPipeline
{
public:

	virtual void VertexShader(VertexData& vertex) = 0;

	virtual void FragmentShader(const VertexData& data, Vector4& fragColor) = 0;

	const Matrix4& GetModelMatrix() const { return modelMatrix; }
	void SetModelMatrix(const Matrix4& model) { modelMatrix = model; }

	const Matrix4& GetViewMatrix() const { return viewMatrix; }
	void SetViewMatrix(const Matrix4& view) { viewMatrix = view; }

	const Matrix4& GetProjectionMatrix() const { return projectionMatrix; }
	void SetProjectionMatrix(const Matrix4& projection) { projectionMatrix = projection; }

	//三角形光栅化,使用Fill Edge 
	static void RasterizeFillEdgeFunction(
		const VertexData& v0,
		const VertexData& v1,
		const VertexData& v2,
		unsigned int screenWidth,
		unsigned int screeneHeight,
		std::vector<VertexData>& rasterizedPoints);

protected:
	Matrix4 modelMatrix;
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
};

