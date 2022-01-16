#pragma once
#include "Vector2.h"
#include "Vector2i.h"
#include "Vector3.h"
#include "Vector4.h"

struct VertexData
{
	Vector4 position;
	Vector3 color;
	Vector3 normal;
	Vector2 texCoordinate;
	Vector4	clipPosition;
	Vector2i screenPosition;

	static void PrePerspCorrection(VertexData& v);
	
	static void AftPrespCorrection(VertexData& v);

	static VertexData BarycentricLerp(const VertexData& v0, const VertexData& v1, const VertexData& v2, Vector3 w);

	static VertexData Lerp(const VertexData& v0, const VertexData& v1, float frac);
};

