#include "Vector4.h"

Vector4 Vector4::operator+(const Vector4& value) const
{
	return { x + value.x,y + value.y,z + value.z };
}

Vector4 Vector4::operator-(const Vector4& value) const
{
	return { x - value.x,y - value.y,z - value.z };
}

float Vector4::operator*(const Vector4& value) const
{
	return x * value.x + y * value.y + z * value.z;
}

bool Vector4::operator==(const Vector4& value) const
{
	return x == value.x && y == value.y && z == value.z;
}

bool Vector4::operator!=(const Vector4& value) const
{
	return !operator==(value);
}

Vector4 Vector4::CrossProduct(const Vector4& value)
{
	return { x * value.y - y * value.x,y * value.z - z * value.y,z * value.x - x * value.z };
}

Vector4& Vector4::operator+=(const Vector4& value)
{
	x += value.x;
	y += value.y;
	z += value.z;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& value)
{
	x -= value.x;
	y -= value.y;
	z -= value.z;
	return *this;
}
