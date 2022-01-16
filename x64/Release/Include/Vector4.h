#pragma once

#include "Vector3.h"

class Vector4
{
public:
	Vector4(float valX = 0.0f, float valY = 0.0f, float valZ = 0.0f, float valW = 1.0f) :x(valX), y(valY), z(valZ), w(valW) {}
	Vector4(const Vector3& value, float valW = 1.0f) :x(value.x), y(value.y), z(value.z), w(valW) {}

	Vector4 operator+(const Vector4& value) const;
	Vector4 operator-(const Vector4& value) const;
	Vector4 operator*(float value) const;
	Vector4& operator+=(const Vector4& value);
	Vector4& operator-=(const Vector4& value);
	Vector4& operator/=(float value);
	Vector4& operator=(const Vector4& value);
	Vector4& operator=(const Vector3& value);

	bool operator==(const Vector4& value) const;
	bool operator!=(const Vector4& value) const;
	float& operator[](int index);
	const float& operator[](int index) const;

	friend Vector4 operator*(float value, const Vector4& vector);
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};

