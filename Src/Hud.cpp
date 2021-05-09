#include "Hud.h";

void Hud::drawHud(char* text, int valeur, float x, float y) {

    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    char buffer[128];
    if(valeur == -1000)
        sprintf(buffer, "%s", text);
    else
        sprintf(buffer, "%s : %d",text, valeur);


    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(x, y);
    int len = strlen(buffer);

    for (int i = 0; i < len  ; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
    }

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);

}
