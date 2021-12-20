#pragma once
#include "Matrix4.h"
class Renderer
{
public:
	static Matrix4 GetProjectionMatrix(float fovy, float aspect, float near, float far);
};

