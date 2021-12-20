#include "Renderer.h"
#include <cmath>

Matrix4 Renderer::GetProjectionMatrix(float fovy, float aspect, float near, float far)
{
	//���͸��ͶӰ�����ǰ�view��������������ϵ����ģ����������projection��������������ϵ��

	Matrix4 result;

	//t/n��ֵ
	float tanHalf = std::tan(fovy / 2.0f);

	//n/t
	float yScale = 1.0 / tanHalf;
	
	//aspect��r/t��һ�����n/r
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
