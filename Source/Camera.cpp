#include "Camera.h"

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

Matrix4 Camera::GetViewMatrix()
{
	//构建lookat矩阵。lookat矩阵本质上是把相机变换矩阵的逆矩阵给拆开了，变成了R-*T-。
	auto zAxis = -cameraDirection;
	auto xAxis = cameraUp.CrossProduct(zAxis).Normalize();
	auto yAxis = zAxis.CrossProduct(xAxis).Normalize();

	Matrix4 rotationMatrix(xAxis, yAxis, zAxis);
	auto inversetRotationMatirx = rotationMatrix.GetTransposed();

	Matrix4 inverseTransformMatrix;
 	inverseTransformMatrix.m[0][3] = -cameraPos.x;
 	inverseTransformMatrix.m[1][3] = -cameraPos.y;
 	inverseTransformMatrix.m[2][3] = -cameraPos.z;

// 	inverseTransformMatrix.m[3][0] = -cameraPos.x;
// 	inverseTransformMatrix.m[3][1] = -cameraPos.y;
// 	inverseTransformMatrix.m[3][2] = -cameraPos.z;

	return inversetRotationMatirx * inverseTransformMatrix;


	//上面如果猜想正确的话，算出来的是左手坐标系的view矩阵，下面这个我要改一下改成右手坐标系的view
// 	auto zAxis = -cameraDirection;
// 	auto xAxis = zAxis.CrossProduct(cameraUp).Normalize();
// 	auto yAxis = xAxis.CrossProduct(zAxis).Normalize();
// 
// 	Matrix4 rotationMatrix(xAxis, yAxis, zAxis);
// 	auto inversetRotationMatirx = rotationMatrix.GetTransposed();
// 
// 	Matrix4 inverseTransformMatrix;
// // 	inverseTransformMatrix.m[0][3] = -cameraPos.x;
// // 	inverseTransformMatrix.m[1][3] = -cameraPos.y;
// // 	inverseTransformMatrix.m[2][3] = -cameraPos.z;
// 
// 	inverseTransformMatrix.m[3][0] = -cameraPos.x;
// 	inverseTransformMatrix.m[3][1] = -cameraPos.y;
// 	inverseTransformMatrix.m[3][2] = -cameraPos.z;
// 
// 
// 	return inversetRotationMatirx * inverseTransformMatrix;
}
