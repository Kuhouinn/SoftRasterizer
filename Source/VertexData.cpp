#include "VertexData.h"

void VertexData::PrePerspCorrection(VertexData& v)
{
	v.position.w = 1.0f / v.clipPosition.w;
	v.position = Vector4(v.position.x * v.position.w, v.position.y * v.position.w, v.position.z * v.position.w, v.position.w);
	v.texCoordinate = v.texCoordinate * v.position.w;
	v.normal = v.normal * v.position.w;
	v.color = v.color * v.position.w;
}

void VertexData::AftPrespCorrection(VertexData& v)
{
	float w = 1.0f / v.position.w;
	//这个*需要确认一下是否正确，因为四个分量都乘了w
	//vector2 和3应该不用确认，所有分量都要乘。
	v.position = v.position * w;
	v.texCoordinate = v.texCoordinate * w;
	v.normal = v.normal * w;
	v.color = v.color * w;
}
