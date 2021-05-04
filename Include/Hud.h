#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"


class Hud {

public :
	void drawHud(char* text, int valeur, float x, float y);
	void chargementTexture(char* filename, unsigned int textureID);

};