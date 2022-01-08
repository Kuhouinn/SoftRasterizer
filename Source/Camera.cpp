#include "Camera.h"

Matrix4 Camera::GetViewMatrix()
{
	//构建lookat矩阵。lookat矩阵本质上是把相机变换矩阵的逆矩阵给拆开了，变成了R-*T-。
	auto zAxis = (cameraPos-target).Normalize();
	auto xAxis = cameraUp.CrossProduct(zAxis).Normalize();
	auto yAxis = zAxis.CrossProduct(xAxis).Normalize();

	Matrix4 rotationMatrix(xAxis, yAxis, zAxis);
	auto inversetRotationMatirx = rotationMatrix.GetTransposed();

	Matrix4 inverseTransformMatrix;
 	inverseTransformMatrix.m[0][3] = -cameraPos.x;
 	inverseTransformMatrix.m[1][3] = -cameraPos.y;
 	inverseTransformMatrix.m[2][3] = -cameraPos.z;

	return inversetRotationMatirx * inverseTransformMatrix;
}
