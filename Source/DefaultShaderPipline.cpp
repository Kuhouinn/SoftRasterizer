#include "DefaultShaderPipline.h"
#include "VertexData.h"

void DefaultShaderPipline::VertexShader(VertexData& vertex)
{
	vertex.position = modelMatrix * vertex.position;
	vertex.clipPosition = projectionMatrix * viewMatrix * vertex.position;
}

void DefaultShaderPipline::FragmentShader(const VertexData& data, Vector4& fragColor)
{
	fragColor = Vector4(data.texCoordinate.x, data.texCoordinate.y, 0.0, 1.0f);
	//fragColor = Vector4(1.0,0.0, 0.0, 1.0f);
}
