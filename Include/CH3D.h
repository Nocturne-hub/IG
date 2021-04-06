#pragma once
#include "TG3D.h"
class CH3D
{
	public:
		float x, y, z;
	private:
		float w;
	public:
		CH3D(void);
		CH3D(float xp, float yp, float zp, float wp);
		CH3D(CH3D* c);

	CH3D mult(const TG3D& mat);

};

