#pragma once
class Vector3
{
public:
	Vector3(float valX = 0.0f, float valY = 0.0f, float valZ = 0.0f) :x(valX), y(valY), z(valZ) {}

	Vector3 operator+(const Vector3& value) const;
	Vector3 operator-(const Vector3& value) const;
	float operator*(const Vector3& value) const;
	Vector3& operator+=(const Vector3& value);
	Vector3& operator-=(const Vector3& value);
	bool operator==(const Vector3& value) const;
	bool operator!=(const Vector3& value) const;

	Vector3 Normalize() const;

	Vector3 CrossProduct(const Vector3& value);
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

