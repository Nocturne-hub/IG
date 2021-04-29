#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Texture/ChargePngFile.h"

class Skybox {
public :
	void drawSkyBox(float x, float y, unsigned int textureId);
};
