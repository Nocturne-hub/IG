#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"

class Skybox {

private :
	
	

public :
	unsigned int texture;
	void drawSkyBox(float x, float y);
	void chargementTexture(char* filename, unsigned int textureID);
};
