#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

struct VertexData
{
	Vector4 position;
	Vector3 color;
	Vector3 normal;
	Vector2 texCoordinate;
	Vector4	clipPosition;
	Vector2 screenPosition;
};

