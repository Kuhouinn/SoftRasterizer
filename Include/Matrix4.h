#pragma once
#include "Vector3.h"

class Vector4;

class Matrix4
{
public:
	Matrix4(const Vector3& baseX = { 1,0,0 }, const Vector3& baseY = { 0,1,0 }, const Vector3& baseZ = { 0,0,1 }, const Vector3& baseW = { 0,0,0 });

	Matrix4 GetTransposed() const;

	void SetScale(const Vector3& scale);

	Matrix4 operator*(const Matrix4& value) const;

	Vector4 operator*(const Vector4& value) const;

	float* operator[](int index);
public:
	float m[4][4] = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

