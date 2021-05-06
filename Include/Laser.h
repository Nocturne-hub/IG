#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Patatoide.h"
#include "Vaisseau.h"

class Laser {
private:
	float posX = 0.0f;
	float posY = 0.0f;
	float posZ = 0.0f;

	float tailleX = 0.0f;
	float tailleY = 0.0f;
	float tailleZ = 0.0f;

public:
	Laser();
	Laser(Vaisseau v, int i);

	float getPosX();
	float getPosY();
	float getPosZ();
	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);

	void mySolidCylindre(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	void mySolidSphere(GLdouble height, GLint slices, GLint stacks);
	void mySolidLaser();

	bool enCollision(Patatoide p);
};