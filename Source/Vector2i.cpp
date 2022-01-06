#include "Vector2i.h"

Vector2i Vector2i::operator+(const Vector2i& value) const
{
	return { x + value.x,y + value.y };
}

Vector2i Vector2i::operator-(const Vector2i& value) const
{
	return { x - value.x,y - value.y };
}

Vector2i Vector2i::operator-() const
{
	return { -x,-y };
}


Vector2i Vector2i::operator*(int value) const
{
	return { x * value,y * value };
}

bool Vector2i::operator==(const Vector2i& value) const
{
	return x == value.x && y == value.y;
}

bool Vector2i::operator!=(const Vector2i& value) const
{
	return !operator==(value);
}

Vector2i& Vector2i::operator+=(const Vector2i& value)
{
	x += value.x;
	y += value.y;
	return *this;
}

Vector2i& Vector2i::operator-=(const Vector2i& value)
{
	x -= value.x;
	y -= value.y;
	return *this;
}

Vector2i operator*(float value, const Vector2i& vector)
{
	return vector * value;
}
