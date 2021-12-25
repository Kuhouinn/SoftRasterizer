#include "DefaultShaderPipline.h"
#include "VertexData.h"

void DefaultShaderPipline::VertexShader(VertexData& vertex)
{
	vertex.position = modelMatrix * vertex.position;
	vertex.clipPosition = projectionMatrix * viewMatrix * vertex.position;
}

void DefaultShaderPipline::FragmentShader(const VertexData& data, Vector4& fragColor)
{

}
