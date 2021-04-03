#include "Vaisseau.h"

void Vaisseau::mySolidVaisseau(double c) {
    double m = c / 2;

    glBegin(GL_TRIANGLES);

    // Dessous  1-3-4
    glVertex3f(-m, m, 0.0f);    //1
    glVertex3f(m, m, 0.0f);     //4
    glVertex3f(0.0f, -m / 2, -0.1f); //3

    // Gauche 1-2-3
    glVertex3f(-m, m, 0.0f);    //1
    glVertex3f(0.0f, m, c);     //2
    glVertex3f(0.0f, -m / 2, -0.1f); //3

    // Droite  4-2-3
    glVertex3f(m, m, 0.0f);     //4
    glVertex3f(0.0f, m, c);     //2
    glVertex3f(0.0f, -m / 2, -0.1f); //3

    // Dessus 1-2-4
    glVertex3f(-m, m, 0.0f);    //1
    glVertex3f(0.0f, m, c);     //2
    glVertex3f(m, m, 0.0f);     //4


    glEnd();

}