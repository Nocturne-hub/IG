#include "Vaisseau.h"
#include "Dir3D.h"

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

void Vaisseau::mySolidVaisseau(float c) {
    float m = c / 2;

    glBegin(GL_TRIANGLES);

    // Dessous  1-3-4
    Pos3D p1 = Pos3D(-m, m, 0.0f);
    Pos3D p2 = Pos3D(0.0, m, -c);
    Pos3D p3 = Pos3D(0.0f, -m/2, -0.1f);
    Pos3D p4 = Pos3D(m, m, 0.0f);

    Dir3D d14 = Dir3D(p1, p4);
    Dir3D d13 = Dir3D(p1, p3);
    Dir3D d12 = Dir3D(p1, p2);

    Dir3D dNorm1 = d14 ^ d13;
    glNormal3f(dNorm1.x, dNorm1.y, dNorm1.z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(p1.x, p1.y, p1.z);    //1
    glTexCoord2f(1.0, 1.0);
    glVertex3f(p4.x, p4.y, p4.z);    //4
    glTexCoord2f(1.0, 0.0);
    glVertex3f(p3.x, p3.y, p3.z);    //3
    glTexCoord2f(0.0, 0.0);
    glVertex3f(p4.x, p4.y, p4.z);

    // Gauche 1-2-3

    Dir3D dNorm2 = d12 ^ d13;
    glNormal3f(dNorm2.x, dNorm2.y, dNorm2.z);
    glVertex3f(p1.x, p1.y, p1.z);    //1
    glVertex3f(p2.x, p2.y, p2.z);    //2
    glVertex3f(p3.x, p3.y, p3.z);    //3

    // Droite  4-2-3

    Dir3D d42 = Dir3D(p4, p2);
    Dir3D d43 = Dir3D(p4, p3);
    Dir3D dNorm3 = d42 ^ d43;
    glNormal3f(dNorm3.x, dNorm3.y, dNorm3.z);
    glVertex3f(p4.x, p4.y, p4.z);    //4
    glVertex3f(p2.x, p2.y, p2.z);    //2
    glVertex3f(p3.x, p3.y, p3.z);    //3

    // Dessus 1-2-4
    Dir3D dNorm4 = d12 ^ d14;
    glNormal3f(dNorm4.x, dNorm4.y, dNorm4.z);
    glVertex3f(p1.x, p1.y, p1.z);    //1
    glVertex3f(p2.x, p2.y, p2.z);    //2
    glVertex3f(p4.x, p4.y, p4.z);    //4

    glEnd();

}

void Vaisseau::initTexture(void) {
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); char* nomFichier = "Emoji1.png";
    printf("%s\n", nomFichier);
    int rx;
    int ry;

    unsigned char* img = chargeImagePng(nomFichier, &rx, &ry);
    printf("%s\n", img);
    if (img) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        free(img);
        printf("Texture chargee %d\n", textureID);
    }
    else {
        glDeleteTextures(1, &textureID);
        textureID = 0;
        printf("Texture non chargee\n");
    }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    
}

