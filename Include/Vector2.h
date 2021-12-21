#pragma once
class Vector2
{
public:
	Vector2(float valX = 0.0f, float valY = 0.0f, float valZ = 0.0f) :x(valX), y(valY), z(valZ) {}

	Vector2 operator+(const Vector2& value) const;
	Vector2 operator-(const Vector2& value) const;
	Vector2& operator+=(const Vector2& value);
	Vector2& operator-=(const Vector2& value);
	bool operator==(const Vector2& value) const;
	bool operator!=(const Vector2& value) const;

	Vector2 operator-()const;
public:
	float x = 0.0f;
	float y = 0.0f;
};

