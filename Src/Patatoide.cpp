#include "Patatoide.h"

#include <math.h>
struct coord_3D {
    GLfloat x = 0.0F;
    GLfloat y = 0.0F;
    GLfloat z = 0.0F;
    GLfloat w = 1.0F;
};

typedef struct coord_3D coord_3D;
typedef float matrice[4][4];
typedef float vecteur[4];


static int aff = 0;
static int pt = 0;
static int maille = 6;
static int texture = 1;

static matrice nrubs =
{ -0.1666666F, 0.5F,      -0.5F,      0.1666666F,
   0.5F      ,-1.0F,       0.5F,      0.0F,
  -0.5F      , 0.0F,       0.5F,      0.0F,
   0.1666666F, 0.6666666F, 0.1666666F,0.0F };
static matrice cr =
{ -0.5F, 1.5F,-1.5F, 0.5F,
   1.0F,-2.5F, 2.0F,-0.5F,
  -0.5F, 0.0F, 0.5F, 0.0F,
   0.0F, 1.0F, 0.0F, 0.0F };
static matrice bezier =
{ -1.0F, 3.0F,-3.0F, 1.0F,
   3.0F,-6.0F, 3.0F, 0.0F,
  -3.0F, 3.0F, 0.0F, 0.0F,
   1.0F, 0.0F, 0.0F, 0.0F };

#define LI 64 
#define LH 64 
GLubyte image[LI][LH][3];

void makeImage(void) {
    int i, j, c;
    for (i = 0; i < LI; i++) {
        for (j = 0; j < LH; j++) {
            c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
            image[i][j][0] = (GLubyte)255;
            image[i][j][1] = (GLubyte)c;
            image[i][j][2] = (GLubyte)c;
        }
    }
}

/*               ATTENTION               */
/* Les produits matrice-vecteur,         */
/* matrice-matrice, la transposition     */
/* et le produit vectoriel implantes     */
/* ci-dessous necessitent                */
/* que les parametres resultats          */
/* soient des tableaux et structures     */
/* differents des parametres d'entree    */

void point(coord_3D* p, coord_3D* n, coord_3D* t) {
    glTexCoord2f(t->x, t->y);
    glNormal3f(n->x, n->y, n->z);
    glVertex3f(p->x, p->y, p->z);
}

void vectoriel(coord_3D* v1, coord_3D* v2, coord_3D* v) {
    v->x = v1->y * v2->z - v1->z * v2->y;
    v->y = v1->z * v2->x - v1->x * v2->z;
    v->z = v1->x * v2->y - v1->y * v2->x;
}

void normalize(coord_3D* n) {
    float d = (float)sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
    if (d != 0.0F) {
        n->x /= d;
        n->y /= d;
        n->z /= d;
    }
}

void transposition(matrice m, matrice t) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t[i][j] = m[j][i];
}

void produitMatriceMatrice(matrice m1, matrice m2, matrice m) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            m[i][j] = 0;
            for (int k = 0; k < 4; k++)
                m[i][j] += m1[i][k] * m2[k][j];
        }
}

void produitMatriceVecteur(matrice m, vecteur v, vecteur r) {
    for (int i = 0; i < 4; i++) {
        r[i] = 0;
        for (int j = 0; j < 4; j++)
            r[i] += m[i][j] * v[j];
    }
}

void produitVecteurMatrice(vecteur v, matrice m, vecteur r) {
    for (int i = 0; i < 4; i++) {
        r[i] = 0;
        for (int j = 0; j < 4; j++)
            r[i] += v[j] * m[j][i];
    }
}

float produitVecteurVecteur(vecteur v1, vecteur v2) {
    float r = 0;
    for (int i = 0; i < 4; i++)
        r += v1[i] * v2[i];
    return(r);
}

void bicubiquePatch(int n, matrice m, matrice mprime, coord_3D* p) {
    int i, j;
    coord_3D** pts = (coord_3D**)malloc(n * sizeof(coord_3D*));
    coord_3D** nms = (coord_3D**)malloc(n * sizeof(coord_3D*));
    coord_3D** tex = (coord_3D**)malloc(n * sizeof(coord_3D*));
    for (i = 0; i < n; i++) {
        tex[i] = (coord_3D*)malloc(n * sizeof(coord_3D));
        pts[i] = (coord_3D*)malloc(n * sizeof(coord_3D));
        nms[i] = (coord_3D*)malloc(n * sizeof(coord_3D));
    }
    matrice tx, a, aa;
    matrice ty, b, bb;
    matrice tz, c, cc;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            a[i][j] = p[i * 4 + j].x;
            b[i][j] = p[i * 4 + j].y;
            c[i][j] = p[i * 4 + j].z;
        }
    matrice trans;
    transposition(mprime, trans);
    produitMatriceMatrice(m, a, aa);
    produitMatriceMatrice(m, b, bb);
    produitMatriceMatrice(m, c, cc);
    produitMatriceMatrice(aa, trans, tx);
    produitMatriceMatrice(bb, trans, ty);
    produitMatriceMatrice(cc, trans, tz);
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float s = (float)i / (float)(n - 1);
            float t = (float)j / (float)(n - 1);
            vecteur S = { s * s * s,s * s,s,1.0F };
            vecteur T = { t * t * t,t * t,t,1.0F };
            vecteur dS = { 3 * s * s,2 * s,1.0F,0.0F };
            vecteur dT = { 3 * t * t,2 * t,1.0F,0.0F };
            vecteur d;
            coord_3D ds, dt;
            produitVecteurMatrice(S, tx, d);
            float x = produitVecteurVecteur(d, T);
            produitVecteurMatrice(dS, tx, d);
            ds.x = produitVecteurVecteur(d, T);
            produitVecteurMatrice(S, tx, d);
            dt.x = produitVecteurVecteur(d, dT);
            produitVecteurMatrice(S, ty, d);
            float y = produitVecteurVecteur(d, T);
            produitVecteurMatrice(dS, ty, d);
            ds.y = produitVecteurVecteur(d, T);
            produitVecteurMatrice(S, ty, d);
            dt.y = produitVecteurVecteur(d, dT);
            produitVecteurMatrice(S, tz, d);
            float z = produitVecteurVecteur(d, T);
            produitVecteurMatrice(dS, tz, d);
            ds.z = produitVecteurVecteur(d, T);
            produitVecteurMatrice(S, tz, d);
            dt.z = produitVecteurVecteur(d, dT);
            vectoriel(&dt, &ds, &nms[i][j]);
            normalize(&nms[i][j]);
            tex[i][j].x = s;
            tex[i][j].y = t;
            pts[i][j].x = x;
            pts[i][j].y = y;
            pts[i][j].z = z;
        }
    }
    glBegin(GL_QUADS);
    for (i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++) {
            point(&pts[i][j], &nms[i][j], &tex[i][j]);
            point(&pts[i + 1][j], &nms[i + 1][j], &tex[i + 1][j]);
            point(&pts[i + 1][j + 1], &nms[i + 1][j + 1], &tex[i + 1][j + 1]);
            point(&pts[i][j + 1], &nms[i][j + 1], &tex[i][j + 1]);
        }
    glEnd();
    for (i = 0; i < n; i++) {
        free(tex[i]);
        free(pts[i]);
        free(nms[i]);
    }
    free(tex);
    free(pts);
    free(nms);
}

void Patatoide::setPosX(float x) {
    posX = x;
}

void Patatoide::setPosY(float y) {
    posY = y;
}

void Patatoide::setPosZ(float z) {
    posZ = z;
}

float Patatoide::getPosX() {
    return posX;
}

float Patatoide::getPosY() {
    return posY;
}

float Patatoide::getPosZ() {
    return posZ;
}

Patatoide::Patatoide(float x, float y, float z, unsigned int textureId ) {
    posX = x;
    posY = y;
    posZ = z;
    texture = textureId;
}

Patatoide::Patatoide() {

}

void Patatoide::boom() {
    alreadyBoomed = true;
}

void Patatoide::deBoom() {
    alreadyBoomed = false;
}

bool Patatoide::isBoomed() {
    return alreadyBoomed;
}


void Patatoide::myPatatoide(GLfloat c) {
    glBindTexture(GL_TEXTURE_2D, texture);
    GLfloat p1[4]  = { 0.0F * c,-0.78F * c, 0.8F * c, 1.0F };
    GLfloat p2[4]  = { 0.3F * c,-0.9F * c, 1.0F * c, 1.0F };
    GLfloat p3[4]  = { 0.63F * c,-0.9F * c, 1.0F * c, 1.0F };
    GLfloat p4[4]  = { 0.9F * c,-0.7F * c, 0.8F * c, 1.0F };
    GLfloat p5[4]  = { 1.2F * c,-0.5F * c, 1.0F * c, 1.0F };
    GLfloat p6[4]  = { 1.2F * c, 0.5F * c, 1.0F * c, 1.0F };
    GLfloat p7[4]  = { 0.77F * c, 0.77F * c, 0.77F * c, 1.0F };
    GLfloat p8[4]  = { 0.5F * c, 1.0F * c, 1.0F * c, 1.0F };
    GLfloat p9[4]  = {-0.5F * c, 1.0F * c, 1.0F * c, 1.0F };
    GLfloat p10[4] = {-1.2F * c, 1.2F * c, 0.8F * c, 1.0F };
    GLfloat p11[4] = {-2.5F * c, 0.5F * c, 1.0F * c, 1.0F };
    GLfloat p12[4] = {-1.5F * c,-0.5F * c, 1.0F * c, 1.0F };

    GLfloat p13[4] = { 0.0F * c,-0.78F * c,-0.8F * c, 1.0F };
    GLfloat p14[4] = { 0.3F * c,-0.9F * c,-1.0F * c, 1.0F };
    GLfloat p15[4] = { 0.63F * c,-0.9F * c,-1.0F * c, 1.0F };
    GLfloat p16[4] = { 0.9F * c,-0.7F * c,-0.8F * c, 1.0F };
    GLfloat p17[4] = { 1.2F * c,-0.5F * c,-1.0F * c, 1.0F };
    GLfloat p18[4] = { 1.2F * c, 0.5F * c,-1.0F * c, 1.0F };
    GLfloat p19[4] = { 0.77F * c, 0.77F * c,-0.77F * c, 1.0F };
    GLfloat p20[4] = { 0.5F * c, 1.0F * c,-1.0F * c, 1.0F };
    GLfloat p21[4] = {-0.5F * c, 1.0F * c,-1.0F * c, 1.0F };
    GLfloat p22[4] = {-1.2F * c, 1.2F * c,-0.8F * c, 1.0F };
    GLfloat p23[4] = {-2.5F * c, 0.5F * c,-1.0F * c, 1.0F };
    GLfloat p24[4] = {-1.5F * c,-0.5F * c,-1.0F * c, 1.0F };
    
    GLfloat p25[4] = { 0.0F * c,-0.8F * c, 0.5F * c, 1.0F };
    GLfloat p26[4] = { 1.0F * c,-0.8F * c, 0.5F * c, 1.0F };
    GLfloat p27[4] = { 1.0F * c, 1.0F * c, 0.5F * c, 1.0F };
    GLfloat p28[4] = {-1.5F * c, 1.5F * c, 0.5F * c, 1.0F };

    GLfloat p29[4] = { 0.0F * c,-1.0F * c,-0.5F * c, 1.0F };
    GLfloat p30[4] = { 1.0F * c,-1.0F * c,-0.5F * c, 1.0F };
    GLfloat p31[4] = { 1.0F * c, 1.0F * c,-0.5F * c, 1.0F };
    GLfloat p32[4] = {-1.5F * c, 1.5F * c,-0.5F * c, 1.0F };
    GLfloat face1[16][4] = {
      {p1[0], p1[1], p1[2], p1[3]},{p2[0], p2[1], p2[2], p2[3]},{p3[0], p3[1], p3[2], p3[3]},{p4[0], p4[1], p4[2], p4[3]},
      {p12[0], p12[1], p12[2], p12[3]},{-0.5F * c,-0.5F * c, 1.5F * c, 1.0F }, { 0.5F * c,-0.5F * c, 1.5F * c, 1.0F },{p5[0], p5[1], p5[2], p5[3]},
      {p11[0], p11[1], p11[2], p11[3]},{-0.5F * c, 0.5F * c, 1.4F * c, 1.0F }, { 0.5F * c, 0.5F * c, 1.4F * c, 1.0F },{p6[0], p6[1], p6[2], p6[3]},
      {p10[0], p10[1], p10[2], p10[3]},{p9[0], p9[1], p9[2], p9[3]},{p8[0], p8[1], p8[2], p8[3]},{p7[0], p7[1], p7[2], p7[3]} };
    GLfloat face2[16][4] = {
      {p10[0], p10[1], p10[2], p10[3]},{p9[0], p9[1], p9[2], p9[3]},{p8[0], p8[1], p8[2], p8[3]},{p7[0], p7[1], p7[2], p7[3]},
      {p28[0], p28[1], p28[2], p28[3]},{-0.5F * c, 2.0F * c, 0.5F * c, 1.0F }, { 0.5F * c, 1.0F * c, 0.5F * c, 1.0F },{p27[0], p27[1], p27[2], p27[3]},
      {p32[0], p32[1], p32[2], p32[3]},{-0.5F * c, 2.0F * c,-0.5F * c, 1.0F }, { 0.5F * c, 1.0F * c,-0.5F * c, 1.0F },{p31[0], p31[1], p31[2], p31[3]},
      {p22[0], p22[1], p22[2], p22[3]},{p21[0], p21[1], p21[2], p21[3]},{p20[0], p20[1], p20[2], p20[3]},{p19[0], p19[1], p19[2], p19[3]} };
    GLfloat face3[16][4] = {
      {p16[0], p16[1], p16[2], p16[3]},{p15[0], p15[1], p15[2], p15[3]},{p14[0], p14[1], p14[2], p14[3]},{p13[0], p13[1], p13[2], p13[3]},
      {p17[0], p17[1], p17[2], p17[3]},{ 0.5F * c,-0.5F * c, -1.5F * c, 1.0F }, {-0.5F * c,-0.5F * c, -1.5F * c, 1.0F },{p24[0], p24[1], p24[2], p24[3]},
      {p18[0], p18[1], p18[2], p18[3]},{ 0.5F * c, 0.5F * c, -1.4F * c, 1.0F }, {-0.5F * c, 0.5F * c, -1.4F * c, 1.0F },{p23[0], p23[1], p23[2], p23[3]},
      {p19[0], p19[1], p19[2], p19[3]},{p20[0], p20[1], p20[2], p20[3]},{p21[0], p21[1], p21[2], p21[3]},{p22[0], p22[1], p22[2], p22[3]} };
    GLfloat face4[16][4] = {
      {p4[0], p4[1], p4[2], p4[3]},{p3[0], p3[1], p3[2], p3[3]},{p2[0], p2[1], p2[2], p2[3]},{p1[0], p1[1], p1[2], p1[3]},
      {p26[0], p26[1], p26[2], p26[3]},{ 0.63F * c,-1.0F * c, 0.5F * c, 1.0F }, { 0.5F * c,-1.0F * c, 0.5F * c, 1.0F },{p25[0], p25[1], p25[2], p25[3]},
      {p30[0], p30[1], p30[2], p30[3]},{ 0.63F * c,-1.0F * c,-0.5F * c, 1.0F }, { 0.5F * c,-1.0F * c,-0.5F * c, 1.0F },{p29[0], p29[1], p29[2], p29[3]},
      {p16[0], p16[1], p16[2], p16[3]},{p15[0], p15[1], p15[2], p15[3]},{p14[0], p14[1], p14[2], p14[3]},{p13[0], p13[1], p13[2], p13[3]} };
    GLfloat face5[16][4] = {
      {p13[0], p13[1], p13[2], p13[3]},{p29[0], p29[1], p29[2], p29[3]},{p25[0], p25[1], p25[2], p25[3]},{p1[0], p1[1], p1[2], p1[3]},
      {p24[0], p24[1], p24[2], p24[3]},{-1.8F * c,-0.5F * c,-0.5F * c, 1.0F }, {-1.8F * c,-0.5F * c, 0.5F * c, 1.0F },{p12[0], p12[1], p12[2], p12[3]},
      {p23[0], p23[1], p23[2], p23[3]},{-4.0F * c, 0.5F * c,-0.5F * c, 1.0F }, {-4.0F * c, 0.5F * c, 0.5F * c, 1.0F },{p11[0], p11[1], p11[2], p11[3]},
      {p22[0], p22[1], p22[2], p22[3]},{p32[0], p32[1], p32[2], p32[3]},{p28[0], p28[1], p28[2], p28[3]},{p10[0], p10[1], p10[2], p10[3]} };
    GLfloat face6[16][4] = {
      {p4[0], p4[1], p4[2], p4[3]},{p26[0], p26[1], p26[2], p26[3]},{p30[0], p30[1], p30[2], p30[3]},{p16[0], p16[1], p16[2], p16[3]},
      {p5[0], p5[1], p5[2], p5[3]},{ 1.3F * c,-0.5F * c, 0.5F * c, 1.0F }, { 1.3F * c,-0.5F * c,-0.5F * c, 1.0F },{p17[0], p17[1], p17[2], p17[3]},
      {p6[0], p6[1], p6[2], p6[3]},{ 1.3F * c, 0.5F * c, 0.5F * c, 1.0F }, { 1.3F * c, 0.5F * c,-0.5F * c, 1.0F },{p18[0], p18[1], p18[2], p18[3]},
      {p7[0], p7[1], p7[2], p7[3]},{p27[0], p27[1], p27[2], p27[3]},{p31[0], p31[1], p31[2], p31[3]},{p19[0], p19[1], p19[2], p19[3]} };


    coord_3D* points_face1 = (coord_3D*)face1;
    coord_3D* points_face2 = (coord_3D*)face2;
    coord_3D* points_face3 = (coord_3D*)face3;
    coord_3D* points_face4 = (coord_3D*)face4;
    coord_3D* points_face5 = (coord_3D*)face5;
    coord_3D* points_face6 = (coord_3D*)face6;
    bicubiquePatch(maille, bezier, bezier, points_face1);
    bicubiquePatch(maille, bezier, bezier, points_face2);
    bicubiquePatch(maille, bezier, bezier, points_face3);
    bicubiquePatch(maille, bezier, bezier, points_face4);
    bicubiquePatch(maille, bezier, bezier, points_face5);
    bicubiquePatch(maille, bezier, bezier, points_face6);
    /*
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
    */
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
        printf("Texture chargee %d : %s\n", textureID, filename);
    }
    else {
        printf("Texture non chargee\n");
    } }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}