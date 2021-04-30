#include "Skybox.h"


GLenum cube_map_target[6] = {
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
};


void Skybox::drawSkyBox(float x, float y) {
    // Taille du cube
    float t = 2.0f;

    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, texture);

    glPushMatrix();
    glLoadIdentity();
    glRotatef(x, 1.0f, 0.0f, 0.0f);
    glRotatef(y, 0.0f, 1.0f, 0.0f);


    glBegin(GL_TRIANGLE_STRIP);     
        glTexCoord3f(-t, -t, -t); glVertex3f(-t, -t, -t);
        glTexCoord3f(-t, t, -t); glVertex3f(-t, t, -t);
        glTexCoord3f(-t, -t, t); glVertex3f(-t, -t, t);
        glTexCoord3f(-t, t, t); glVertex3f(-t, t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // X Positif
        glTexCoord3f(t, -t, -t);
        glVertex3f(t, -t, -t);
        glTexCoord3f(t, -t, t);
        glVertex3f(t, -t, t);
        glTexCoord3f(t, t, -t);
        glVertex3f(t, t, -t);
        glTexCoord3f(t, t, t);
        glVertex3f(t, t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Y Négatif    
        glTexCoord3f(-t, -t, -t);
        glVertex3f(-t, -t, -t);
        glTexCoord3f(-t, -t, t);
        glVertex3f(-t, -t, t);
        glTexCoord3f(t, -t, -t);
        glVertex3f(t, -t, -t);
        glTexCoord3f(t, -t, t);
        glVertex3f(t, -t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Y Positif        
        glTexCoord3f(-t, t, -t);
        glVertex3f(-t, t, -t);
        glTexCoord3f(t, t, -t);
        glVertex3f(t, t, -t);
        glTexCoord3f(-t, t, t);
        glVertex3f(-t, t, t);
        glTexCoord3f(t, t, t);
        glVertex3f(t, t, t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Z Négatif        
        glTexCoord3f(-t, -t, -t);
        glVertex3f(-t, -t, -t);
        glTexCoord3f(t, -t, -t);
        glVertex3f(t, -t, -t);
        glTexCoord3f(-t, t, -t);
        glVertex3f(-t, t, -t);
        glTexCoord3f(t, t, -t);
        glVertex3f(t, t, -t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);            // Z Positif    
        glTexCoord3f(-t, -t, t);
        glVertex3f(-t, -t, t);
        glTexCoord3f(-t, t, t);
        glVertex3f(-t, t, t);
        glTexCoord3f(t, -t, t);
        glVertex3f(t, -t, t);
        glTexCoord3f(t, t, t);
        glVertex3f(t, t, t);
    glEnd();

    // Réinitialisation de la matrice ModelView
    glPopMatrix();
}


void Skybox::chargementTexture(char* filename, unsigned int textureID) {


    unsigned char* textures[6];

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    texture = textureID;

    { int rx;
    int ry;
    unsigned char* img = chargeImagePng(filename, &rx, &ry);
    if (img) {
        textures[0] = img;
        textures[1] = img;
        textures[2] = img;
        textures[3] = img;
        textures[4] = img;
        textures[5] = img;

        for (int i = 0; i < 6; i++) {
            glTexImage2D(cube_map_target[i], 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[i]);

        }
        free(img);
    }
    else {
        printf("Texture non chargée\n");
    } }
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
}