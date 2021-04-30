#include "Skybox.h"

void Skybox::drawSkyBox(float x, float y, unsigned int textureId) {
    // Taille du cube
    float t = 1.0f;

    // Utilisation de la texture CubeMap
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, textureId);

    // R�glage de l'orientation
    glPushMatrix();
    glLoadIdentity();
    glRotatef(0.0, 1.0f, 0.0f, 0.0f);
    glRotatef(0.0, 0.0f, 1.0f, 0.0f);


    // Rendu de la g�om�trie
    glBegin(GL_TRIANGLE_STRIP);     
    glTexCoord3f(-t, -t, -t); glVertex3f(-t, -t, -t);
    glTexCoord3f(-t, t, -t); glVertex3f(-t, t, -t);
    glTexCoord3f(-t, -t, t); glVertex3f(-t, -t, t);
    glTexCoord3f(-t, t, t); glVertex3f(-t, t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // X Positif
    glTexCoord3f(t, -t, -t); glVertex3f(t, -t, -t);
    glTexCoord3f(t, -t, t); glVertex3f(t, -t, t);
    glTexCoord3f(t, t, -t); glVertex3f(t, t, -t);
    glTexCoord3f(t, t, t); glVertex3f(t, t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Y N�gatif    
    glTexCoord3f(-t, -t, -t); glVertex3f(-t, -t, -t);
    glTexCoord3f(-t, -t, t); glVertex3f(-t, -t, t);
    glTexCoord3f(t, -t, -t); glVertex3f(t, -t, -t);
    glTexCoord3f(t, -t, t); glVertex3f(t, -t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Y Positif        
    glTexCoord3f(-t, t, -t); glVertex3f(-t, t, -t);
    glTexCoord3f(t, t, -t); glVertex3f(t, t, -t);
    glTexCoord3f(-t, t, t); glVertex3f(-t, t, t);
    glTexCoord3f(t, t, t); glVertex3f(t, t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Z N�gatif        
    glTexCoord3f(-t, -t, -t); glVertex3f(-t, -t, -t);
    glTexCoord3f(t, -t, -t); glVertex3f(t, -t, -t);
    glTexCoord3f(-t, t, -t); glVertex3f(-t, t, -t);
    glTexCoord3f(t, t, -t); glVertex3f(t, t, -t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Z Positif    
    glTexCoord3f(-t, -t, t); glVertex3f(-t, -t, t);
    glTexCoord3f(-t, t, t); glVertex3f(-t, t, t);
    glTexCoord3f(t, -t, t); glVertex3f(t, -t, t);
    glTexCoord3f(t, t, t); glVertex3f(t, t, t);
    glEnd();

    // R�initialisation de la matrice ModelView
    glPopMatrix();
}