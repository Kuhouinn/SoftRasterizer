#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class Camera
{
public:
	Camera() {}

	const Vector3& GetCameraPosition() { return cameraPos; }

	const Vector3& GetCameraDirection() { return cameraDirection; }

	const Vector3& GetCameraUp() { return cameraUp; }

	float GetCameraFov() { return fov; }

	void SetCameraPosition(const Vector3& position) { cameraPos = position; }
	
	//统一在传进来之前标准化一下
	void SetCameraDirection(const Vector3& direction) { cameraDirection = direction; }

	void SetCameraUp(const Vector3& up) { cameraUp = up; }

	void SetMouseCallback(double xOffset, double yOffset);

	void SetScrollCallback(double yOffset);

	Matrix4 GetViewMatrix();

private:
	float pitch = 0.0f;
	float yaw = -90.0f;
	float fov = 45.0f;
	Vector3 cameraPos = { 0.0f, 0.0f, 3.0f };
	Vector3 cameraDirection = { 0.0f, 0.0f, -1.0f };
	Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };
};


