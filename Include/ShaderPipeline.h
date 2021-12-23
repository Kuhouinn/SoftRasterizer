#pragma once
#include <vector>

#include "Matrix4.h"

struct VertexData;

class ShaderPipeline
{
public:

	void VertexShader(VertexData& vertex);

	void SetModelMatrix(const Matrix4& model) { modelMatrix = model; }

	void SetViewMatrix(const Matrix4& view) { viewMatrix = view; }

	void SetProjectionMatrix(const Matrix4& projection) { projectionMatrix = projection; }

	//三角形光栅化,使用Fill Edge 
	static void RasterizeFillEdgeFunction(
		const VertexData& v0,
		const VertexData& v1,
		const VertexData& v2,
		unsigned int screenWidth,
		unsigned int screeneHeight,
		std::vector<VertexData>& rasterizedPoints);

private:
	Matrix4 modelMatrix;
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
};

