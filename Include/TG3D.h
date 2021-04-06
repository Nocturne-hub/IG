#pragma once
class TG3D
{
	public:
		float mat[4][4];
		TG3D(void);

		TG3D mult(const TG3D& rhs);    // Compose this et rhs (this.rhs) et retourne le résultat

};

