#include "Laser.h"

Laser::Laser() {
    tailleX = 0.15f;
    tailleY = 0.15f;
    tailleZ = 1.0f;
}

Laser::Laser(Vaisseau v, int i) {
    tailleX = 0.15f;
    tailleY = 0.15f;
    tailleZ = 1.0f;
    posX = v.coordCanons[i][0];
    posY = v.coordCanons[i][1];
    if (i == 0) {
        posZ = -0.5;
    }
    else {
        posZ = 1.9;
    }
    
}


float Laser::getPosX() {
    return posX;
}

float Laser::getPosY() {
    return posY;
}

float Laser::getPosZ() {
    return posZ;
}

void Laser::setPosX(float x) {
    posX = x;
}

void Laser::setPosY(float y) {
    posY = y;
}

void Laser::setPosZ(float z) {
    posZ = z;
}
void Laser::mySolidCylindre(GLdouble base, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj* theQuadric;
    theQuadric = gluNewQuadric();
    gluQuadricDrawStyle(theQuadric, GLU_FILL);
    gluQuadricNormals(theQuadric, GLU_SMOOTH);
    gluCylinder(theQuadric, base, base, height, slices, stacks);
    gluDeleteQuadric(theQuadric);
}

void Laser::mySolidSphere(GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj* sphere = NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, height, slices, stacks);
    gluDeleteQuadric(sphere);

}
void Laser::mySolidLaser(){
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    mySolidSphere(tailleX/2, 50, 50);
    mySolidCylindre(tailleX / 2, tailleZ, 50, 50);
    glTranslatef(0.0f, 0.0f, tailleZ);
    mySolidSphere(tailleX/2, 50, 50);
    glPopMatrix();
}

bool Laser::enCollision(Patatoide p) {

    if (p.isBoomed()) {
        return false;
    }

    float absX = abs(p.getPosX() - posX);
    float absY = abs(p.getPosY() - posY);
    float absZ = abs(p.getPosZ() - posZ);


    if (absX <= tailleX + 1.0f && absY <= tailleY + 1.0f && absZ <= tailleZ + 1.0f) {
        return true;
    }

    return false;
}