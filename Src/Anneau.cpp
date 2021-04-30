#include "Anneau.h"

float Anneau::getPosX() {
    return posAnneauX;
}

float Anneau::getPosY() {
    return posAnneauY;
}

float Anneau::getPosZ() {
    return posAnneauZ;
}

void Anneau::setPosX(float x) {
    posAnneauX = x;
}

void Anneau::setPosY(float y) {
    posAnneauY = y;
}

void Anneau::setPosZ(float z) {
    posAnneauZ = z;
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