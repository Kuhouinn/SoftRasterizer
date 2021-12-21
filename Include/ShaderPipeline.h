#pragma once
#include <vector>

struct VertexData;

class ShaderPipeline
{
public:
	static void RasterizeFillEdgeFunction(
		const VertexData& v0,
		const VertexData& v1,
		const VertexData& v2,
		unsigned int screenWidth,
		unsigned int screeneHeight,
		std::vector<VertexData>& rasterizedPoints);
};

