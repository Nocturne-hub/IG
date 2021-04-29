#include "Patatoide.h"

void Patatoide::setPosX(float x) {
    posX = x;
}

void Patatoide::setPosY(float y) {
    posY = y;
}

void Patatoide::setPosZ(float z) {
    posZ = z;
}

float Patatoide::getPosX() {
    return posX;
}

float Patatoide::getPosY() {
    return posY;
}

float Patatoide::getPosZ() {
    return posZ;
}

Patatoide::Patatoide(float x, float y, float z ) {
    posX = x;
    posY = y;
    posZ = z;
}


void Patatoide::myPatatoide(double c) {
    double m = c / 2;

    glBegin(GL_QUADS);

    glNormal3f(0, 0, 1.0);
    //devant
    glVertex3f(-m, m, m);
    glVertex3f(m, m, m);
    glVertex3f(m, -m, m);
    glVertex3f(-m, -m, m);

    glNormal3f(0, 0, -1.0);
    //arriere
    glVertex3f(-m, m, -m);
    glVertex3f(m, m, -m);
    glVertex3f(m, -m, -m);
    glVertex3f(-m, -m, -m);

    glNormal3f(-1.0, 0, 0.0);
    //gauche
    glVertex3f(-m, m, m);
    glVertex3f(-m, m, -m);
    glVertex3f(-m, -m, -m);
    glVertex3f(-m, -m, m);

    glNormal3f(1.0, 0, 0.0);
    //droite
    glVertex3f(m, m, m);
    glVertex3f(m, -m, m);
    glVertex3f(m, -m, -m);
    glVertex3f(m, m, -m);

    glNormal3f(0.0, 1.0, 0.0);
    //dessus
    glVertex3f(-m, m, m);
    glVertex3f(m, m, m);
    glVertex3f(m, m, -m);
    glVertex3f(-m, m, -m);

    glNormal3f(0.0, -1.0, 0.0);
    //dessous
    glVertex3f(-m, -m, m);
    glVertex3f(m, -m, m);
    glVertex3f(m, -m, -m);
    glVertex3f(-m, -m, -m);


    glEnd();
}
