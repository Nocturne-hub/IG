#include "Sc3D.h"
Sc3D::Sc3D(float sx, float sy, float sz)
	: TG3D()
{
	mat[0][0] = sx;
	mat[1][1] = sy;
	mat[2][2] = sz;
}
