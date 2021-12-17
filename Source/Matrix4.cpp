#include "Matrix4.h"

Matrix4::Matrix4(const Vector3& baseX, const Vector3& baseY, const Vector3& baseZ, const Vector3& baseW)
{
	m[0][0] = baseX.x;
	m[1][0] = baseX.y;
	m[2][0] = baseX.z;

	m[0][1] = baseY.x;
	m[1][1] = baseY.y;
	m[2][1] = baseY.z;

	m[0][2] = baseZ.x;
	m[1][2] = baseZ.y;
	m[2][2] = baseZ.z;

	m[0][3] = baseW.x;
	m[1][3] = baseW.y;
	m[2][3] = baseW.z;
}

Matrix4 Matrix4::GetTransposed() const
{
	Matrix4	result;

	result.m[0][0] = m[0][0];
	result.m[0][1] = m[1][0];
	result.m[0][2] = m[2][0];
	result.m[0][3] = m[3][0];

	result.m[1][0] = m[0][1];
	result.m[1][1] = m[1][1];
	result.m[1][2] = m[2][1];
	result.m[1][3] = m[3][1];

	result.m[2][0] = m[0][2];
	result.m[2][1] = m[1][2];
	result.m[2][2] = m[2][2];
	result.m[2][3] = m[3][2];

	result.m[3][0] = m[0][3];
	result.m[3][1] = m[1][3];
	result.m[3][2] = m[2][3];
	result.m[3][3] = m[3][3];

	return result;
}

Matrix4 Matrix4::operator*(const Matrix4& val) const
{
	Matrix4 result;

	for (auto i=0;i<4;i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			result.m[i][j] = m[i][0] * val.m[0][j] + m[i][1] * val.m[1][j] + m[i][2] * val.m[2][j] + m[i][3] * val.m[3][j];
		}
	}

	return result;
}
