#include "Renderer.h"
#include <cmath>

Matrix4 Renderer::GetProjectionMatrix(float fovy, float aspect, float near, float far)
{
	//这个透视投影矩阵是按view矩阵是右手坐标系计算的，计算出来的projection矩阵是左手坐标系的

	Matrix4 result;

	//t/n的值
	float tanHalf = std::tan(fovy / 2.0f);

	//n/t
	float yScale = 1.0 / tanHalf;
	
	//aspect是r/t，一除变成n/r
	float xScale = yScale / aspect;
	float farMinusNear = far - near;
	float farAddNear = far + near;

	result[0][0] = xScale;
	result[1][1] = yScale;
	result[2][2] = -farAddNear / farMinusNear;
	result[2][3] = -1;
	result[3][2] = -2.0 * far * near / farAddNear;

	return result;
}
