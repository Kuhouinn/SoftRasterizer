#include "Vector3.h"
#include <cmath>

Vector3 Vector3::operator+(const Vector3& value) const
{
	return { x + value.x,y + value.y,z + value.z };
}

Vector3 Vector3::operator-(const Vector3& value) const
{
	return { x - value.x,y - value.y,z - value.z };
}

Vector3 Vector3::operator-() const
{
	return { -x,-y,-z };
}

float Vector3::operator*(const Vector3& value) const
{
	return x * value.x + y * value.y + z * value.z;
}

Vector3& Vector3::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3& Vector3::operator*(float value)
{
	x *= value;
	y *= value;
	z *= value;
	
	return *this;
}

float Vector3::Length()
{
	return std::sqrt(x * x + y * y + z * z);
}

bool Vector3::operator==(const Vector3& value) const
{
	return x == value.x && y == value.y && z == value.z;
}

bool Vector3::operator!=(const Vector3& value) const
{
	return !operator==(value);
}

Vector3 Vector3::Normalize() const
{
	auto denominator = 1.0f / std::sqrt(x * x + y * y + z * z);
	return { x * denominator,y * denominator,z * denominator };
}

Vector3 Vector3::CrossProduct(const Vector3& value)
{
	return { y * value.z - z * value.y,z * value.x - x * value.z,x * value.y - y * value.x };
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

Vector3 operator*(float value, const Vector3& vector)
{
	return vector * value;
}
