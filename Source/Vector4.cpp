#include "Vector4.h"

#include "Vector3.h"

Vector4 Vector4::operator+(const Vector4& value) const
{
	return { x + value.x,y + value.y,z + value.z,w + value.w };
}

Vector4 Vector4::operator-(const Vector4& value) const
{
	return { x - value.x,y - value.y,z - value.z ,w - value.w };
}

Vector4 Vector4::operator*(float value) const
{
	return { x * value,y * value,z * value,w * value };
}

Vector4& Vector4::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
}

Vector4& Vector4::operator=(const Vector4& value)
{
	x = value.x;
	y = value.y;
	z = value.z;
	w = value.w;
}

Vector4& Vector4::operator=(const Vector3& value)
{
	x = value.x;
	y = value.y;
	z = value.z;
}

float& Vector4::operator[](int index)
{
	switch (index)
	{
	case 0: return &x;
	case 1: return &y;
	case 2: return &z;
	case 3: return &w;
	}
}

const float& Vector4::operator[](int index) const
{
	return operator[](index);
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
