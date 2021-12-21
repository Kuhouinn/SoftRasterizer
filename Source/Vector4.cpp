#include "Vector4.h"

Vector4 Vector4::operator+(const Vector4& value) const
{
	return { x + value.x,y + value.y,z + value.z,w + value.w };
}

Vector4 Vector4::operator-(const Vector4& value) const
{
	return { x - value.x,y - value.y,z - value.z ,w - value.w };
}

bool Vector4::operator==(const Vector4& value) const
{
	return x == value.x && y == value.y && z == value.z && w == value.w;
}

bool Vector4::operator!=(const Vector4& value) const
{
	return !operator==(value);
}

Vector4& Vector4::operator+=(const Vector4& value)
{
	x += value.x;
	y += value.y;
	z += value.z;
	w += value.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& value)
{
	x -= value.x;
	y -= value.y;
	z -= value.z;
	w -= value.w;
	return *this;
}
