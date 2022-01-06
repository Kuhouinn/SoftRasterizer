#pragma once
#include "Vector3.h"

class DirectionalLight
{
public:
	DirectionalLight() {};
public:
	Vector3 amibent = {0.5f,0.5f,0.5f};
	Vector3 diffuse = {0.8f,0.8f,0.8f};
	Vector3 specular = {1.0f,1.0f,1.0f};
	Vector3 direction = { -1.0,-3.0f,-3.0f };
	//Vector3 direction = { -3.0f,0.0f,0.0f };
};

