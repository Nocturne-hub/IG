#include "Anneau.h"

Anneau::Anneau(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;

    alreadyMiamed = false;
}


Anneau::Anneau() {
    alreadyMiamed = false;
}


float Anneau::getPosX() {
    return posX;
}
float Anneau::getPosY() {
    return posY;
}
float Anneau::getPosZ() {
    return posZ;
}

void Anneau::setPosX(float x) {
    posX = x;
}

void Anneau::setPosY(float y) {
    posY = y;
}

void Anneau::setPosZ(float z) {
    posZ = z;
}

bool Anneau::isMiamed() {
    return alreadyMiamed;
}

void Anneau::miam() {
    alreadyMiamed = true;
}

void Anneau::unMiam() {
    alreadyMiamed = false;
}



void Anneau::myPrecious(double rayonTube, double rayonTore, double angleI, double angleF, int nbTube, int nbTore) {
    for (int i = 0; i < nbTore; i++) {
        float da = angleF - angleI;
        float alphai = angleI + da * i / nbTore;
        float alphaj = alphai + da / nbTore;
        float cosalphai = cos(alphai);
        float sinalphai = sin(alphai);
        float cosalphaj = cos(alphaj);
        float sinalphaj = sin(alphaj);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= nbTube; j++) {
            float beta = 2 * M_PI * j / nbTube;
            float cosbeta = cos(beta);
            float sinbita = sin(beta);
            float x1 = (rayonTore + rayonTube * cosbeta) * cosalphai;
            float y1 = (rayonTore + rayonTube * cosbeta) * sinalphai;
            float z1 = rayonTube * sinbita;
            glNormal3f(cosbeta * cosalphai, cosbeta * sinalphai, sinbita);
            glVertex3f(x1, y1, z1);
            float x2 = (rayonTore + rayonTube * cosbeta) * cosalphaj;
            float y2 = (rayonTore + rayonTube * cosbeta) * sinalphaj;
            float z2 = rayonTube * sinbita;
            glNormal3f(cosbeta * cosalphaj, cosbeta * sinalphaj, sinbita);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}

void Anneau::myPrecious(double rayonTube, double rayonTore, int nbFTube, int nbFTore) {
    myPrecious(rayonTube, rayonTore, 0.0, 2 * M_PI, nbFTube, nbFTore);
}