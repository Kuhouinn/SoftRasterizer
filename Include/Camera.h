#pragma once
#include "Vector3.h"

class Camera
{
public:
	Camera();
	const Vector3& GetCameraPosition() { return cameraPos; }
	const Vector3& GetCameraFront() { return cameraFront; }
	const Vector3& GetCameraUp() { return cameraUp; }
	float GetCameraFov() { return fov; }
	void SetCameraPosition(const Vector3& position) { cameraPos = position; }
	void SetCameraFront(const Vector3& front) { cameraFront = front; }
	void SetCameraUp(const Vector3& up) { cameraUp = up; }
	void SetMouseCallback(double xOffset, double yOffset);
	void SetScrollCallback(double yOffset);

private:
	float pitch;
	float yaw;
	float fov;
	Vector3 cameraPos;
	Vector3 cameraFront;
	Vector3 cameraUp;
};


