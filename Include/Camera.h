#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class Camera
{
public:
	Camera() {}

	const Vector3& GetCameraPosition() { return cameraPos; }

	const Vector3& GetCameraTarget() { return target; }

	Vector3 GetCameraDirection() { return (cameraPos-target).Normalize(); }

	const Vector3& GetCameraUp() { return cameraUp; }

	float GetCameraFov() { return fov; }

	void SetCameraPosition(const Vector3& position) { cameraPos = position; }
	
	void SetCameraTarget(const Vector3& value) { target = value; }

	void SetCameraUp(const Vector3& up) { cameraUp = up; }

	Matrix4 GetViewMatrix();

private:
	float pitch = 0.0f;
	float yaw = -90.0f;
	float fov = 45.0f;
	Vector3 cameraPos = { 0.0f, 0.0f, 3.0f };
	Vector3 target = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };
};


