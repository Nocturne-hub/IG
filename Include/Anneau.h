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

	public:
		void myPrecious(double rayonTube, double rayonTore, double angleI, double angleF, int nbTube, int nbTore);
		void myPrecious(double rayonTube, double rayonTore, int nbFTube, int nbFTore);
};

