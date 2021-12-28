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
