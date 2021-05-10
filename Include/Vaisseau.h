#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"
#include "Patatoide.h"
#include "Anneau.h"

#define PI 3.1415926535898
class Vaisseau {
	private:
		float posX = 0.0f;
		float posY = 0.0f;
		float posZ = 0.0f;

		float hitX = 0.0f;
		float hitY = 0.0f;
		float hitZ = 0.0f;

		float taille = 1.0f;
		float tailleX = 0.0f;
		float tailleY = 0.0f;
		float tailleZ = 0.0f;

		int vie = 3;
		int score = 0;

	public:

		Vaisseau();
		Vaisseau(float t);

		float coordCanons[3][3] = { {0.0f, -1.0f, -1.5f}, {1.25f, 0.9f, 1.0f}, {-1.25f, 0.9f, 1.0f} };

		unsigned int texture;
		void mySolidVaisseau(float c);
		float getPosX();
		float getPosY();
		float getPosZ();
		void setPosX(float x);
		void setPosY(float y);
		void setPosZ(float z);
		int getScore();
		int getVie();
		void setVie(int val);

		void chargementTexture(char* filename, unsigned int textureID);
		void mySolidCanon();
		void mySolidCube(double c);
		void mySolidSpaceShip();
		void mySolidShipWing(double c, bool rigth);
		void mySolidSpaceShipBody(GLdouble base, GLdouble height, GLint slices, GLint stacks);
		void mySolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
		void mySolidCylindre(GLdouble base, GLdouble height, GLint slices, GLint stacks);
		void Quadrilatere(double c);
		void mySolidSphere(GLdouble height, GLint slices, GLint stacks);
		bool enCollision(Patatoide p);
		bool miamAnneau(Anneau a);
		void reset();
};

