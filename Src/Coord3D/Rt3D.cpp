#include "Rt3D.h"
Rt3D::Rt3D(float angle, Dir3D& dir)
	: TG3D()
{
	float c = cos(angle);
	float s = sin(angle);
	Dir3D dirNorm = dir.normalize();
	mat[0][0] = dirNorm.x * dirNorm.x + c * (1.0F - dirNorm.x * dirNorm.x);
	mat[0][1] = dirNorm.x * dirNorm.y * (1.0F - c) - dirNorm.z * s;
	mat[0][2] = dirNorm.x * dirNorm.z * (1.0F - c) + dirNorm.y * s;
	mat[0][3] = 0.0;

	mat[1][0] = dirNorm.x * dirNorm.y * (1.0F - c) + dirNorm.z * s;
	mat[1][1] = dirNorm.y * dirNorm.y + c * (1.0F - dirNorm.y * dirNorm.y);
	mat[1][2] = dirNorm.y * dirNorm.z * (1.0F - c) - dirNorm.x * s;
	mat[1][3] = 0.0;

	mat[2][0] = dirNorm.x * dirNorm.z * (1.0F - c) - dirNorm.y * s;
	mat[2][1] = dirNorm.y * dirNorm.z * (1.0F - c) + dirNorm.x * s;
	mat[2][2] = dirNorm.z * dirNorm.z + c * (1.0F - dirNorm.z * dirNorm.z);
	mat[2][3] = 0.0;

	mat[3][0] = 0.0;
	mat[3][1] = 0.0;
	mat[3][2] = 0.0;
	mat[3][3] = 1.0;
}
