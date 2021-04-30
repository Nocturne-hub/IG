#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
class Anneau {
	private:
		#ifndef M_PI
		#define M_PI 3.14159265358979323846264338327950288
		#endif
		float posAnneauX = 0.0f;
		float posAnneauY = 0.0f;
		float posAnneauZ= 0.0f;

	public:
		float getPosX();
		float getPosY();
		float getPosZ();
		void setPosX(float x);
		void setPosY(float y);
		void setPosZ(float z);
		void myPrecious(double rayonTube, double rayonTore, double angleI, double angleF, int nbTube, int nbTore);
		void myPrecious(double rayonTube, double rayonTore, int nbFTube, int nbFTore);
};

