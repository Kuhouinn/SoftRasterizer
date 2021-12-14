#include "Camera.h"

Camera::Camera() :pitch(0.0), yaw(-90.0), fov(45.0), cameraPos(Vector3(0.0f, 0.0f, 3.0f)), cameraFront(Vector3(0.0f, 0.0f, -1.0f)), cameraUp(Vector3(0.0f, 1.0f, 0.0f))
{

}

void Camera::SetMouseCallback(double xOffset, double yOffset)
{
// 	float sensitivity = 0.1f;
// 	xOffset *= sensitivity;
// 	yOffset *= sensitivity;
// 	yaw += xOffset;
// 	pitch += yOffset;
// 	if (pitch > 89.0f)
// 	{
// 		pitch = 89.0f;
// 	}
// 	if (pitch < -89.0f)
// 	{
// 		pitch = -89.0f;
// 	}
// 	/*
// 	cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
// 	cameraFront.y = sin(glm::radians(pitch));
// 	cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
// 	cameraFront = glm::normalize(cameraFront);
// 	*/
// 	Vector3 front;
// 	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
// 	front.y = sin(glm::radians(pitch));
// 
// 	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
// 	cameraFront = glm::normalize(front);
}

void Camera::SetScrollCallback(double yOffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yOffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}