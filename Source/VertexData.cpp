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
	v.position = v.position * w;
	v.texCoordinate = v.texCoordinate * w;
	v.normal = v.normal * w;
	v.color = v.color * w;
}

VertexData VertexData::BarycentricLerp(const VertexData& v0, const VertexData& v1, const VertexData& v2, Vector3 w)
{
	VertexData result;
	result.position = w.x * v0.position + w.y * v1.position + w.z * v2.position;
	result.color = w.x * v0.color + w.y * v1.color + w.z * v2.color;
	result.normal = w.x * v0.normal + w.y * v1.normal + w.z * v2.normal;
	result.texCoordinate = w.x * v0.texCoordinate + w.y * v1.texCoordinate + w.z * v2.texCoordinate;
	result.clipPosition = w.x * v0.clipPosition + w.y * v1.clipPosition + w.z * v2.clipPosition;

	return result;
}

VertexData VertexData::Lerp(const VertexData& v0, const VertexData& v1, float frac)
{
	VertexData result;
	result.position = (1.0f - frac) * v0.position + frac * v1.position;
	result.color = (1.0f - frac) * v0.color + frac * v1.color;
	result.normal = (1.0f - frac) * v0.normal + frac * v1.normal;
	result.texCoordinate = (1.0f - frac) * v0.texCoordinate + frac * v1.texCoordinate;
	result.clipPosition = (1.0f - frac) * v0.clipPosition + frac * v1.clipPosition;

	return result;
}
