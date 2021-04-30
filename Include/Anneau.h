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

		float posX;
		float posY;
		float posZ;

		bool alreadyMiamed = false;

	public:
		Anneau();
		Anneau(float x, float y, float z);


		void myPrecious(double rayonTube, double rayonTore, double angleI, double angleF, int nbTube, int nbTore);
		void myPrecious(double rayonTube, double rayonTore, int nbFTube, int nbFTore);

		void miam();
		bool isMiamed();
		void unMiam();

		float getPosX();
		float getPosY();
		float getPosZ();

		void setPosX(float);
		void setPosY(float);
		void setPosZ(float);
};

