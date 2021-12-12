#include "Vector3.h"

Vector3 Vector3::operator+(const Vector3& value) const
{
	return { x + value.x,y + value.y,z + value.z };
}

Vector3 Vector3::operator-(const Vector3& value) const
{
	return { x - value.x,y - value.y,z - value.z };
}

float Vector3::operator*(const Vector3& value) const
{
	return x * value.x + y * value.y + z * value.z;
}

bool Vector3::operator==(const Vector3& value) const
{
	return x == value.x && y == value.y && z == value.z;
}

bool Vector3::operator!=(const Vector3& value) const
{
	return !operator==(value);
}

Vector3 Vector3::CrossProduct(const Vector3& value)
{
	return { x * value.y - y * value.x,y * value.z - z * value.y,z * value.x - x * value.z };
}

Vector3& Vector3::operator+=(const Vector3& value)
{
	x += value.x;
	y += value.y;
	z += value.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& value)
{
	x -= value.x;
	y -= value.y;
	z -= value.z;
	return *this;
}
