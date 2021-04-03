#include "Patatoide.h"

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
    //arrire
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
