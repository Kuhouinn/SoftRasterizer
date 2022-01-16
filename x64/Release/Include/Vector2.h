#pragma once
class Vector2
{
public:
	Vector2(float valX = 0.0f, float valY = 0.0f) :x(valX), y(valY) {}

	Vector2 operator+(const Vector2& value) const;
	Vector2 operator-(const Vector2& value) const;
	Vector2 operator*(float value) const;
	Vector2& operator+=(const Vector2& value);
	Vector2& operator-=(const Vector2& value);
	bool operator==(const Vector2& value) const;
	bool operator!=(const Vector2& value) const;

	friend Vector2 operator*(float value, const Vector2& vector);

	Vector2 operator-()const;
public:
	float x = 0.0f;
	float y = 0.0f;
};

