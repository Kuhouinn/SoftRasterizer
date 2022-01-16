#pragma once
#include "Vector3.h"

class Matrix3
{
public:
	Matrix3(const Vector3& baseX = { 1,0,0 }, const Vector3& baseY = { 0,1,0 }, const Vector3& baseZ = { 0,0,1 });
public:
	float m[3][3] = {1,0,0,
		0,1,0,
		0,0,1};
};

