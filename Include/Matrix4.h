#pragma once
#include "Vector3.h"

class Matrix4
{
public:
	Matrix4(const Vector3& baseX = { 1,0,0 }, const Vector3& baseY = { 0,1,0 }, const Vector3& baseZ = { 0,0,1 }, const Vector3& baseW = { 0,0,0 });

	Matrix4 GetTransposed() const;

	Matrix4 operator*(const Matrix4& val) const;
public:
	float m[4][4] = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

