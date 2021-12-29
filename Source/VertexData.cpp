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
	//���*��Ҫȷ��һ���Ƿ���ȷ����Ϊ�ĸ�����������w
	//vector2 ��3Ӧ�ò���ȷ�ϣ����з�����Ҫ�ˡ�
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
	result.screenPosition.x = w.x * v0.screenPosition.x + w.y * v1.screenPosition.x + w.z * v2.screenPosition.x;
	result.screenPosition.y = w.x * v0.screenPosition.y + w.y * v1.screenPosition.y + w.z * v2.screenPosition.y;

	return result;
}
