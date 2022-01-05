#include "LightingShaderPipline.h"
#include "VertexData.h"

void LightingShaderPipline::VertexShader(VertexData& vertex)
{
	vertex.position = modelMatrix * vertex.position;
	vertex.clipPosition = projectionMatrix * viewMatrix * vertex.position;
}

void LightingShaderPipline::FragmentShader(const VertexData& data, Vector4& fragColor)
{
	fragColor = Texture2D(diffuseTextureId, data.texCoordinate);
}
