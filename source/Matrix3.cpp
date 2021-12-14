#include "Matrix3.h"

Matrix3::Matrix3(const Vector3& baseX, const Vector3& baseY, const Vector3& baseZ)
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
}
