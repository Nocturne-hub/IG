#include "Vaisseau.h"

void Vaisseau::mySolidVaisseau(float c) {
    float m = c / 2;

    glBegin(GL_TRIANGLES);

    // Dessous  1-3-4
    
    glVertex3f(-m, m, 0.0f);    //1
    glVertex3f(m, m, 0.0f);     //4
    glVertex3f(0.0f, -m / 2, -0.1f); //3

    // Gauche 1-2-3
    glVertex3f(-m, m, 0.0f);    //1
    glVertex3f(0.0f, m, -c);     //2
    glVertex3f(0.0f, -m / 2, -0.1f); //3

    // Droite  4-2-3
    glVertex3f(m, m, 0.0f);     //4
    glVertex3f(0.0f, m, -c);     //2
    glVertex3f(0.0f, -m / 2, -0.1f); //3

    // Dessus 1-2-4
    glVertex3f(-m, m, 0.0f);    //1
    glVertex3f(0.0f, m, -c);     //2
    glVertex3f(m, m, 0.0f);     //4


    glEnd();

}

float Vaisseau::getPosX() {
    return posX;
}

float Vaisseau::getPosY() {
    return posY;
}

float Vaisseau::getPosZ() {
    return posZ;
}

void Vaisseau::setPosX(float x) {
    posX = x;
}

void Vaisseau::setPosY(float y) {
    posY = y;
}

void Vaisseau::setPosZ(float z) {
    posZ = z;
}
