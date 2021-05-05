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
	float angleRotation = 0.0f;
	float axeRotationX = 0.0f;
	float axeRotationY = 0.0f;
	float axeRotationZ = 0.0f;
	int direction = 0.0f;
	float speed = 0.0f;
	float speedRotation = 0.0f;

	bool alreadyBoomed = false;

public:

	Patatoide(float x, float y, float z, unsigned int textureId);
	Patatoide();
	
	unsigned int texture;
	void myPatatoide(GLfloat c);
	float getPosX();
	float getPosY();
	float getPosZ();
	float getAngleRotation();
	float getAxeRotationX();
	float getAxeRotationY();
	float getAxeRotationZ();
	int getDirection();
	float getSpeed();
	float getSpeedRotation();

	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
	void setAngleRotation(float angle);
	void setAxeRotationX(float axe);
	void setAxeRotationY(float axe);
	void setAxeRotationZ(float axe);
	void setDirection(int dir);
	void setSpeed(float speed);
	void setSpeedRotation(float speedRotation);

	void boom();
	bool isBoomed();
	void deBoom();

	void chargementTexture(char* filename, unsigned int textureID);
};
