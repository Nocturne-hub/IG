#pragma once

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"
class Patatoide {
	private:
		float posPatatoideX = 0.0f;
		float posPatatoideY = 0.0f;
		float posPatatoideZ = 0.0f;
	public:
		unsigned int texture;
		float getPosX();
		float getPosY();
		float getPosZ();
		void setPosX(float x);
		void setPosY(float y);
		void setPosZ(float z);
		void myPatatoide(double c);
		void chargementTexture(char* filename, unsigned int textureID);
};

