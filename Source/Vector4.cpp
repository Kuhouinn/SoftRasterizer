#include "Vector4.h"

Vector4 Vector4::operator+(const Vector4& value) const
{
	return { x + value.x,y + value.y,z + value.z,w + value.w };
}

Vector4 Vector4::operator-(const Vector4& value) const
{
	return { x - value.x,y - value.y,z - value.z ,w - value.w };
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
