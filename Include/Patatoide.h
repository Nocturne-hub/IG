#pragma once

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"
class Patatoide {
private:
	float posX = 0.0f;
	float posY = 0.0f;
	float posZ = 0.0f;
public:

	Patatoide(float x, float y, float z);
	
	void myPatatoide(double c);
	float getPosX();
	float getPosY();
	float getPosZ();

	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);

	public:
		unsigned int texture;
		void myPatatoide(double c);
		void chargementTexture(char* filename, unsigned int textureID);
};
