#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Vaisseau {
	private:
		float posX = 0.0f;
		float posY = 0.0f;
		float posZ = 0.0f;

	public:
		void mySolidVaisseau(float c);
		float getPosX();
		float getPosY();
		float getPosZ();
		void setPosX(float x);
		void setPosY(float y);
		void setPosZ(float z);

};

