#pragma once

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"
class Patatoide {
	public:
		unsigned int texture;
		void myPatatoide(double c);
		void chargementTexture(char* filename, unsigned int textureID);
};

