#include "Vaisseau.h"
#include "Patatoide.h"
#include "Anneau.h"
#include "Skybox.h"
#include <time.h>
#include <iostream>

#define PI 3.1415926535898
#define NBANNEAU 5
#define NBPATATOIDE 10

/* Variables globales                           */

static int wTx = 640;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre
static bool filDeFer = false;
static float angle = 0.0;
static bool animation = false;
static bool gauche = true;
static bool isMouse = false;
static bool firstPerson = true;
static bool lumiere = true;

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };

static int rz = 0;
static int mouseX = 0;
static bool touches[] = { false, false, false, false };

static float speedAnneauZ = 0.3f;
static float speedPatatoideZ = 0.5f;
static float speedDeplacement = 0.9f;

static bool texture = true;
static unsigned int texturesSkyBox[6];
static unsigned int textureID[3] = { 0,0,0 };

Vaisseau v;
Skybox skybox;
Patatoide patatoides[NBPATATOIDE];
Anneau anneaux[NBANNEAU];

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */
static void initAnneaux() {
    float posAnneauZ = -15.0f;
    for (int i = 0; i < NBANNEAU; i++) {
        float nPosAnneauX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
        float nPosAnneauY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
        anneaux[i].setPosX(nPosAnneauX);
        anneaux[i].setPosY(nPosAnneauY);
        anneaux[i].setPosZ(posAnneauZ);
        posAnneauZ -= 30.0f;
    }
}

static void initPatatoides() {
    for (int i = 0; i < NBPATATOIDE; i++) {
        float nPosAnneauX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
        float nPosAnneauY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
        float nPosAnneauZ = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / -90.0)) - 15.0;
        patatoides[i].setPosX(nPosAnneauX);
        patatoides[i].setPosY(nPosAnneauY);
        patatoides[i].setPosZ(nPosAnneauZ);
        patatoides[i].chargementTexture("textureAsteroide.png", textureID[1]);
        patatoides[i].texture = textureID[1];
    }
}

static void init(void) {
    const GLfloat shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, rouge);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, jaune);
    //glLightfv(GL_LIGHT2, GL_DIFFUSE, bleu);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glGenTextures(2, textureID);
    v.chargementTexture("textureVaisseau.png", textureID[0]);
    v.texture = textureID[0];
    srand((unsigned int)time(0));
    initAnneaux();
    initPatatoides();
    //sb.chargementTexture("Emoji3.png", textureID[2]);
    //sb.texture = textureID[2];
}

static void initSkybox() {
    int rx, ry;
}

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
        for (int i = 0; i < NBPATATOIDE; i++) {
            glPushMatrix();
            glTranslatef(patatoides[i].getPosX(), patatoides[i].getPosY(), patatoides[i].getPosZ());
            //glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
            patatoides[i].myPatatoide(1.5f);
            glPopMatrix();
        }

        for (int i = 0; i < NBANNEAU; i++) {
            glPushMatrix();
            glTranslatef(anneaux[i].getPosX(), anneaux[i].getPosY(), anneaux[i].getPosZ());
            // glMaterialfv(GL_FRONT, GL_DIFFUSE, jaune);
            anneaux[i].myPrecious(0.1, 3.0, 18, 72);
            glPopMatrix();
        }

        glPushMatrix();
            glTranslatef(v.getPosX(), v.getPosY(), v.getPosZ());
            //glMaterialfv(GL_FRONT, GL_DIFFUSE, bleu);
            v.mySolidSpaceShip(1.0f);
        glPopMatrix();
        
        
   glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    if (texture) {
        glEnable(GL_TEXTURE_2D);
    }else {
        glDisable(GL_TEXTURE_2D);
    }

    if (lumiere) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
    int rotate = gauche ? -1.0 : 1.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /*glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    skybox.drawSkyBox(v.getPosX(), v.getPosX(),1);*/
    

    /*const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
    const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);*/
    glPushMatrix();

    float cameraPosX = firstPerson ? v.getPosX() : v.getPosX();
    float cameraPosY = firstPerson ? v.getPosY() : v.getPosY() + 5.0;
    float cameraPosZ = firstPerson ? v.getPosZ() -2.0 : v.getPosZ() + 10.0;

    float cameraLookX = firstPerson ? v.getPosX() : v.getPosX();
    float cameraLookY = firstPerson ? v.getPosY() : v.getPosY();
    float cameraLookZ = firstPerson ? v.getPosZ() - 3.0 : -(v.getPosZ() + 0.5);
    printf("Vaisseau x,y,z : %f %f %f\n", v.getPosX(), v.getPosY(), v.getPosZ());
    printf("Camera x,y,z : %f %f %f\n", cameraPosX, cameraPosY, cameraPosZ);
    printf("Camera look x,y,z : %f %f %f\n", cameraLookX, cameraLookY, cameraLookZ);

    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, cameraLookX, cameraLookY, cameraLookZ, 0.0, 1.0, 1.0);
    
    if (filDeFer)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glRotatef(angle, rotate, 0, 0);
    glRotatef(rz, 0, 1.0, 0);

    
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

/* Fonction executee lors d'un changeme nt       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx, int wy) {
    printf("R\n");
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10.0, 10.0, -10.0, 10.0, -100.0, 100.0);
    gluPerspective(70.0F, (float)wx / wy, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
    //angle += 0.1;
    for (int i = 0; i < NBANNEAU; i++) {
        if (anneaux[i].getPosZ() > 6.0f)
        {
            anneaux[i].setPosZ(-(NBANNEAU * 30.0));
            //srand((unsigned int)time(0));

            float nPosAnneauX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
            float nPosAnneauY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
            anneaux[i].setPosX(nPosAnneauX);
            anneaux[i].setPosY(nPosAnneauY);
            printf("PosX for ring %d = %f\n", i, nPosAnneauX);
            printf("PosY for ring %d = %f\n", i, nPosAnneauY);
        }
        else {

            anneaux[i].setPosZ(anneaux[i].getPosZ()+speedAnneauZ);
            printf("PosZ for ring %d = %f\n", i, anneaux[i].getPosZ() + speedAnneauZ);
        }
    }

    for (int i = 0; i < NBPATATOIDE; i++) {
        if (patatoides[i].getPosZ() > 6.0f)
        {
            patatoides[i].setPosZ(-(NBANNEAU*30));
            //srand((unsigned int)time(0));

            float nPosPatatoideX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
            float nPosPatatoideY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
            patatoides[i].setPosX(nPosPatatoideX);
            patatoides[i].setPosY(nPosPatatoideY);
            printf("PosX for patatoide %d = %f\n", i, nPosPatatoideX);
            printf("PosY for patatoide %d = %f\n", i, nPosPatatoideY);
        }
        else {

            patatoides[i].setPosZ(patatoides[i].getPosZ() + speedAnneauZ);
            printf("PosZ for patatoide %d = %f\n", i, patatoides[i].getPosZ() + speedPatatoideZ);
        }
    }
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
    case 0x1B:
        exit(0);
        break;
    case 0x20:
        printf("espace");
        filDeFer = !filDeFer;
        glutPostRedisplay();
        break;
    case 0xd:
        printf("entree");
        animation = !animation;
        if (animation)
            glutIdleFunc(idle);
        else
            glutIdleFunc(NULL);
        glutPostRedisplay();
        break;
    }
}

static void deplacement() {
    if (touches[0]) {
        v.setPosX(v.getPosX() - speedDeplacement);
    }
    if (touches[1]) {
        v.setPosX(v.getPosX() + speedDeplacement);
    }
    if (touches[2]) {
        v.setPosY(v.getPosY() + speedDeplacement);
    }
    if (touches[3]) {
        v.setPosY(v.getPosY() - speedDeplacement);
    }
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
    printf("S  %4d %4d %4d\n", specialKey, x, y);
    switch (specialKey) {
    case GLUT_KEY_LEFT:
        touches[0] = true;
        deplacement();
        break;
    case GLUT_KEY_RIGHT:
        touches[1] = true;
        deplacement();
        break;
    case GLUT_KEY_UP:
        touches[2] = true;
        deplacement();
        break;
    case GLUT_KEY_DOWN:
        touches[3] = true;
        deplacement();
        break;
    case GLUT_KEY_F1:
        firstPerson = !firstPerson;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F2:
        texture = !texture;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F3:
        lumiere = !lumiere;
        glutPostRedisplay();
        break;
    }
}

static void specialUp(int specialKey, int x, int y) {
    switch (specialKey) {
    case GLUT_KEY_LEFT:
        touches[0] = false;
        break;
    case GLUT_KEY_RIGHT:
        touches[1] = false;
        break;
    case GLUT_KEY_UP:
        touches[2] = false;
        break;
    case GLUT_KEY_DOWN:
        touches[3] = false;
        break;
    }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
    rz += (mouseX - x);
    mouseX = x;
    glutPostRedisplay();

}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x, int y) {
    printf("PM %4d %4d\n", x, y);
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
    printf("Bye\n");
}

/* Fonction principale                          */

int main(int argc, char** argv) {

    atexit(clean);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Gestion événementielle de GLUt");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    //glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}
