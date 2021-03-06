#include "Vaisseau.h"
#include "Dir3D.h"

Vaisseau::Vaisseau() {
    tailleX = taille * 2.5f;
    tailleY = taille * 1.5f;
    tailleZ = taille * 3.5f;

    score = 0;
}


Vaisseau::Vaisseau(float t) {
    taille = t;

    tailleX = t * 2.5f;
    tailleY = t * 1.5f;
    tailleZ = t * 3.5f;

    score = 0;
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

int Vaisseau::getScore() {
    return score;
}

int Vaisseau::getVie() {
    return vie;
}

void Vaisseau::setVie(int val) {
    vie = val;
}

bool Vaisseau::enCollision(Patatoide p) {
    if (p.isBoomed()) {
        return false;
    }

    float absX = abs(p.getPosX() - posX);
    float absY = abs(p.getPosY() - posY);
    float absZ = abs(p.getPosZ() - posZ);

    if (absX <= tailleX && absY <= (tailleY) && absZ <= tailleZ) {
        vie--;
        return true;
    }

    return false;
}

bool Vaisseau::miamAnneau(Anneau a) {
    if (a.isMiamed()) {
        return false;
    }

    float absX = abs(a.getPosX() - posX);
    float absY = abs(a.getPosY() - posY);
    float absZ = abs(a.getPosZ() - posZ);

    if (absX <= tailleX && absY <= (tailleY + 4.0) && absZ <= tailleZ) {
        score++;
        return true;
    }

    return false;
}


void Vaisseau::mySolidVaisseau(float c) {
    float m = c / 2;
    glBindTexture(GL_TEXTURE_2D, texture);

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
    glTexCoord2f(0, 1);
    glVertex3f(p1.x, p1.y, p1.z);    //1
    glTexCoord2f(1, 0);
    glVertex3f(p4.x, p4.y, p4.z);    //4
    glTexCoord2f(0, 0);
    glVertex3f(p3.x, p3.y, p3.z);    //3

    // Gauche 1-2-3

    Dir3D dNorm2 = d12 ^ d13;
    glNormal3f(dNorm2.x, dNorm2.y, dNorm2.z);
    glTexCoord2f(1, 1);
    glVertex3f(p1.x, p1.y, p1.z);    //1
    glTexCoord2f(1, 0);
    glVertex3f(p2.x, p2.y, p2.z);    //2
    glTexCoord2f(0, 0);
    glVertex3f(p3.x, p3.y, p3.z);    //3

    // Droite  4-2-3

    Dir3D d42 = Dir3D(p4, p2);
    Dir3D d43 = Dir3D(p4, p3);
    Dir3D dNorm3 = d42 ^ d43;
    glNormal3f(dNorm3.x, dNorm3.y, dNorm3.z);
    glTexCoord2f(1, 1);
    glVertex3f(p4.x, p4.y, p4.z);    //4
    glTexCoord2f(1, 0);
    glVertex3f(p2.x, p2.y, p2.z);    //2
    glTexCoord2f(0, 0);
    glVertex3f(p3.x, p3.y, p3.z);    //3

    // Dessus 1-2-4
    Dir3D dNorm4 = d12 ^ d14;
    glNormal3f(dNorm4.x, dNorm4.y, dNorm4.z);
    glTexCoord2f(1, 1);
    glVertex3f(p1.x, p1.y, p1.z);    //1
    glTexCoord2f(1, 0);
    glVertex3f(p2.x, p2.y, p2.z);    //2
    glTexCoord2f(0, 0);
    glVertex3f(p4.x, p4.y, p4.z);    //4

    glEnd();

}

void Vaisseau::chargementTexture(char* filename, unsigned int textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    { int rx;
    int ry;
    unsigned char* img = chargeImagePng(filename, &rx, &ry);
    if (img) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        free(img);
    }
    else {
        printf("Texture non charg?e\n");
    } }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Vaisseau::Quadrilatere(double c) {
    double m = c / 2;

    glBegin(GL_QUADS);

    glNormal3f(0, 0, 1.0);
    //devant
    glTexCoord2f(1, 0);
    glVertex3f(-m, m, c);
    glTexCoord2f(1, 1);
    glVertex3f(m, m, c);
    glTexCoord2f(0, 1);
    glVertex3f(m, -m, c);
    glTexCoord2f(0, 0);
    glVertex3f(-m, -m, c);

    glNormal3f(0, 0, -1.0);
    //arriere
    glTexCoord2f(1, 0);
    glVertex3f(-m, m, -m);
    glTexCoord2f(1, 1);
    glVertex3f(m, m, -m / 5);
    glTexCoord2f(0, 1);
    glVertex3f(m, -m, -m / 5);
    glTexCoord2f(0, 0);
    glVertex3f(-m, -m, -m);

    glNormal3f(-1.0, 0, 0.0);
    //gauche
    glTexCoord2f(1, 0);
    glVertex3f(-m, m, c);
    glTexCoord2f(1, 1);
    glVertex3f(-m, m, -m);
    glTexCoord2f(0, 1);
    glVertex3f(-m, -m, -m);
    glTexCoord2f(0, 0);
    glVertex3f(-m, -m, c);

    glNormal3f(1.0, 0, 0.0);
    //droite
    glTexCoord2f(1, 0);
    glVertex3f(m, m, c);
    glTexCoord2f(1, 1);
    glVertex3f(m, -m, c);
    glTexCoord2f(0, 1);
    glVertex3f(m, -m, -m / 5);
    glTexCoord2f(0, 0);
    glVertex3f(m, m, -m / 5);

    glNormal3f(0.0, 1.0, 0.0);
    //dessus
    glTexCoord2f(1, 0);
    glVertex3f(-m, m, c);
    glTexCoord2f(1, 1);
    glVertex3f(m, m, c);
    glTexCoord2f(0, 1);
    glVertex3f(m, m, -m / 5);
    glTexCoord2f(0, 0);
    glVertex3f(-m, m, -m);

    glNormal3f(0.0, -1.0, 0.0);
    //dessous
    glTexCoord2f(1, 0);
    glVertex3f(-m, -m, c);
    glTexCoord2f(1, 1);
    glVertex3f(m, -m, c);
    glTexCoord2f(0, 1);
    glVertex3f(m, -m, -m / 5);
    glTexCoord2f(0, 0);
    glVertex3f(-m, -m, -m);

    glEnd();
}

void Vaisseau::mySolidCylindre(GLdouble base, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj* theQuadric;
    theQuadric = gluNewQuadric();
    gluQuadricDrawStyle(theQuadric, GLU_FILL);
    gluQuadricTexture(theQuadric, TRUE);
    gluQuadricNormals(theQuadric, GLU_SMOOTH);
    gluCylinder(theQuadric, base, base, height, slices, stacks);
    gluDeleteQuadric(theQuadric);
}

void Vaisseau::mySolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj* cone = NULL;
    cone = gluNewQuadric();
    gluQuadricDrawStyle(cone, GLU_FILL);
    gluQuadricTexture(cone, TRUE);
    gluQuadricNormals(cone, GLU_SMOOTH);
    gluCylinder(cone, base, 0.0f, height, slices, stacks);
    gluDeleteQuadric(cone);
}

void Vaisseau::mySolidCube(double c) {
    double c2 = c / 2;
    glBegin(GL_QUADS);
    //Face avant
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-c2, c2, c2);
    glTexCoord2f(1, 1);
    glVertex3f(c2, c2, c2);
    glTexCoord2f(1, 0);
    glVertex3f(c2, -c2, c2);
    glTexCoord2f(0, 0);
    glVertex3f(-c2, -c2, c2);

    //Face arriere
    glNormal3f(0.0f, 0.0f, -1.0f);

    glTexCoord2f(0, 1);
    glVertex3f(-c2, c2, -c2);
    glTexCoord2f(1, 1);
    glVertex3f(c2, c2, -c2);
    glTexCoord2f(1, 0);
    glVertex3f(c2, -c2, -c2);
    glTexCoord2f(0, 0);
    glVertex3f(-c2, -c2, -c2);

    //Face gauche
    glNormal3f(-1.0f, 0.0f, 0.0f);

    glTexCoord2f(0, 1);
    glVertex3f(-c2, c2, -c2);
    glTexCoord2f(1, 1);
    glVertex3f(-c2, c2, c2);
    glTexCoord2f(1, 0);
    glVertex3f(-c2, -c2, c2);
    glTexCoord2f(0, 0);
    glVertex3f(-c2, -c2, -c2);

    //Face droite
    glNormal3f(1.0f, 0.0f, 0.0f);

    glTexCoord2f(1, 1);
    glVertex3f(c2, c2, c2);
    glTexCoord2f(0, 1);
    glVertex3f(c2, c2, -c2);
    glTexCoord2f(0, 0);
    glVertex3f(c2, -c2, -c2);
    glTexCoord2f(1, 0);
    glVertex3f(c2, -c2, c2);

    //face dessus
    glNormal3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(0, 1);
    glVertex3f(-c2, c2, -c2);
    glTexCoord2f(1, 1);
    glVertex3f(c2, c2, -c2);
    glTexCoord2f(1, 0);
    glVertex3f(c2, c2, c2);
    glTexCoord2f(0, 0);
    glVertex3f(-c2, c2, c2);

    //face dessous
    glNormal3f(0.0f, -1.0f, 0.0f);

    glTexCoord2f(0, 1);
    glVertex3f(c2, -c2, -c2);
    glTexCoord2f(1, 1);
    glVertex3f(-c2, -c2, -c2);
    glTexCoord2f(1, 0);
    glVertex3f(-c2, -c2, c2);
    glTexCoord2f(0, 0);
    glVertex3f(c2, -c2, c2);


    glEnd();
}

void Vaisseau::mySolidCanon() {
    glPushMatrix();
    mySolidCube(0.4);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    mySolidCylindre(0.15, 1.5, 50, 50);
    glPopMatrix();
}

void Vaisseau::mySolidShipWing(double c, bool rigth) {
    glPushMatrix();
    if (rigth) {
        glTranslatef(-c * 2.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
        Quadrilatere(c);
        glPopMatrix();
        glTranslatef(0.0f, 0.0f, c);
        mySolidCone(c / 2, c, 50, 50);
        glPushMatrix();
        glTranslatef(0.0f, c/2+0.25, -c/1.5);
        mySolidCanon();
        glPopMatrix();
        
    }
    else {
        Quadrilatere(c);
        glTranslatef(0.0f, 0.0f, c);
        mySolidCone(c / 2, c, 50, 50);
        glPushMatrix();
        glTranslatef(0.0f, c/2+0.25, -c/1.5);
        mySolidCanon();
        glPopMatrix();
    }
    glPopMatrix();
}

void Vaisseau::mySolidSphere(GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj* sphere = NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, height, slices, stacks);
    gluDeleteQuadric(sphere);
}

void Vaisseau::mySolidSpaceShipBody(GLdouble base, GLdouble height, GLint slices, GLint stacks) {
    glPushMatrix();
    mySolidSphere(base, 50, 50);
    mySolidCylindre(base, height, 500, 50);
    glTranslatef(0.0f, 0.0f, height);
    mySolidSphere(base, 50, 50);
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -base, 0.0f);
    mySolidCanon();
    glPopMatrix();
    glPopMatrix();
}

void Vaisseau::mySolidSpaceShip() {
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, taille * 3);
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    mySolidSpaceShipBody(taille, taille *3, 50, 50);     //Main du vaisseau
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -taille *1.25f, -0.05f);
    mySolidVaisseau(taille *1.5f);                //Aileron du vaisseau
    glPopMatrix();
    glPushMatrix();
    glTranslatef(taille *1.25f, 0.0f, -taille);
    if (vie >= 3) {
        mySolidShipWing(taille * 1.25f, true); //Aile droite
    }
    if (vie >= 2) {
        mySolidShipWing(taille * 1.25f, false);                   //Aille gauche
    }
    
    glPopMatrix();
    glPopMatrix();
}

void Vaisseau::reset() {
    score = 0;
    vie = 3;

    posX = 0.0f;
    posY = 0.0f;
}