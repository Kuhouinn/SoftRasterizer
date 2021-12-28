#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& value) const
{
	return { x + value.x,y + value.y};
}

Vector2 Vector2::operator-(const Vector2& value) const
{
	return { x - value.x,y - value.y};
}

Vector2 Vector2::operator-() const
{
	return { -x,-y};
}


Vector2 Vector2::operator*(float value) const
{
	return { x * value,y * value };
}

bool Vector2::operator==(const Vector2& value) const
{
	return x == value.x && y == value.y;
}

bool Vector2::operator!=(const Vector2& value) const
{
	return !operator==(value);
}

Vector2& Vector2::operator+=(const Vector2& value)
{
	x += value.x;
	y += value.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& value)
{
	x -= value.x;
	y -= value.y;
	return *this;
}