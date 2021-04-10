#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"

class Vaisseau {
	private:
		float posX = 0.0f;
		float posY = 0.0f;
		float posZ = 0.0f;

	public:
		unsigned int textureID;
		void mySolidVaisseau(float c);
		float getPosX();
		float getPosY();
		float getPosZ();
		void setPosX(float x);
		void setPosY(float y);
		void setPosZ(float z);
		void initTexture();
		void mySolidSpaceShip(double c);
		void mySolidShipWing(double c);
		void mySolidSpaceShipBody(GLdouble base, GLdouble height, GLint slices, GLint stacks);
		void mySolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
		void mySolidCylindre(GLdouble base, GLdouble height, GLint slices, GLint stacks);
		void Quadrilatere(double c);


};

