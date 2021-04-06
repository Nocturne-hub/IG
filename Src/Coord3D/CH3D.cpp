#include "CH3D.h"

CH3D::CH3D(void) : x(0.0F), y(0.0F), z(0.0F), w(1.0F) {}

CH3D::CH3D(float xp, float yp, float zp, float wp) :
	x(xp), y(yp), z(zp), w(wp) {}

CH3D::CH3D(CH3D* c) : x(c->x), y(c->y), z(c->z), w(c->w) {}

CH3D  CH3D::mult(const TG3D& mat)
{
	CH3D res;
	res.x = this->x * mat.mat[0][0] + this->y * mat.mat[0][1] + this->z * mat.mat[0][2] + this->w * mat.mat[0][3];
	res.y = this->x * mat.mat[1][0] + this->y * mat.mat[1][1] + this->z * mat.mat[1][2] + this->w * mat.mat[1][3];
	res.z = this->x * mat.mat[2][0] + this->y * mat.mat[2][1] + this->z * mat.mat[2][2] + this->w * mat.mat[2][3];
	res.w = this->x * mat.mat[3][0] + this->y * mat.mat[3][1] + this->z * mat.mat[3][2] + this->w * mat.mat[3][3];
	return res;
}
