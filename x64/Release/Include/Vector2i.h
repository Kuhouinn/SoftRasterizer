#pragma once
class Vector2i
{
public:
	Vector2i(int valX = 0, int valY = 0) :x(valX), y(valY) {}

	Vector2i operator+(const Vector2i& value) const;
	Vector2i operator-(const Vector2i& value) const;
	Vector2i operator*(int value) const;
	Vector2i& operator+=(const Vector2i& value);
	Vector2i& operator-=(const Vector2i& value);
	bool operator==(const Vector2i& value) const;
	bool operator!=(const Vector2i& value) const;

	friend Vector2i operator*(float value, const Vector2i& vector);

	Vector2i operator-()const;
public:
	int x = 0;
	int y = 0;
};

