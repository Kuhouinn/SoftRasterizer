#pragma once
class Vector4
{
public:
	Vector4(float valX = 0.0f, float valY = 0.0f, float valZ = 0.0f, float valW = 1.0f) :x(valX), y(valY), z(valZ), w(valW) {}

	Vector4 operator+(const Vector4& value) const;
	Vector4 operator-(const Vector4& value) const;
	Vector4& operator+=(const Vector4& value);
	Vector4& operator-=(const Vector4& value);
	bool operator==(const Vector4& value) const;
	bool operator!=(const Vector4& value) const;
	float& operator[](int index);
	const float& operator[](int index) const;
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};

