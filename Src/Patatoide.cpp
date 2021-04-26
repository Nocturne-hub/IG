#include "Patatoide.h"

void Patatoide::myPatatoide(double c) {
    double m = c / 2;
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    glNormal3f(0, 0, 1.0);
    //devant
    glTexCoord2f(1, 1);
    glVertex3f(-m, m, m);
    glTexCoord2f(1, 0);
    glVertex3f(m, m, m);
    glTexCoord2f(0, 0);
    glVertex3f(m, -m, m);
    glTexCoord2f(0, 1);
    glVertex3f(-m, -m, m);

    glNormal3f(0, 0, -1.0);
    //arriere
    glTexCoord2f(1, 1);
    glVertex3f(-m, m, -m);
    glTexCoord2f(1, 0);
    glVertex3f(m, m, -m);
    glTexCoord2f(0, 0);
    glVertex3f(m, -m, -m);
    glTexCoord2f(0, 1);
    glVertex3f(-m, -m, -m);

    glNormal3f(-1.0, 0, 0.0);
    //gauche
    glTexCoord2f(1, 1);
    glVertex3f(-m, m, m);
    glTexCoord2f(1, 0);
    glVertex3f(-m, m, -m);
    glTexCoord2f(0, 0);
    glVertex3f(-m, -m, -m);
    glTexCoord2f(0, 1);
    glVertex3f(-m, -m, m);

    glNormal3f(1.0, 0, 0.0);
    //droite
    glTexCoord2f(1, 1);
    glVertex3f(m, m, m);
    glTexCoord2f(1, 0);
    glVertex3f(m, -m, m);
    glTexCoord2f(0, 0);
    glVertex3f(m, -m, -m);
    glTexCoord2f(0, 1);
    glVertex3f(m, m, -m);

    glNormal3f(0.0, 1.0, 0.0);
    //dessus
    glTexCoord2f(1, 1);
    glVertex3f(-m, m, m);
    glTexCoord2f(1, 0);
    glVertex3f(m, m, m);
    glTexCoord2f(0, 0);
    glVertex3f(m, m, -m);
    glTexCoord2f(0, 1);
    glVertex3f(-m, m, -m);

    glNormal3f(0.0, -1.0, 0.0);
    //dessous
    glTexCoord2f(1, 1);
    glVertex3f(-m, -m, m);
    glTexCoord2f(1, 0);
    glVertex3f(m, -m, m);
    glTexCoord2f(0, 0);
    glVertex3f(m, -m, -m);
    glTexCoord2f(0, 1);
    glVertex3f(-m, -m, -m);


    glEnd();
}

void Patatoide::chargementTexture(char* filename, unsigned int textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    { int rx;
    int ry;
    unsigned char* img = chargeImagePng(filename, &rx, &ry);
    if (img) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        free(img);
        printf("Texture chargée %d : %s\n", textureID, filename);
    }
    else {
        printf("Texture non chargée\n");
    } }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}