#include "Vaisseau.h"
#include "Patatoide.h"
#include "Anneau.h"
#include "Skybox.h"
#include "Hud.h"
#include "Laser.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

#define PI 3.1415926535898
#define NBANNEAU 5
#define NBPATATOIDE 30

/* Variables globales                           */

static int wTx = 1280;              // Resolution horizontale de la fenetre
static int wTy = 720;              // Resolution verticale de la fenetre
static int wPx = (glutGet(GLUT_SCREEN_WIDTH) - wTx) /2;               // Position horizontale de la fenetre
static int wPy = (glutGet(GLUT_SCREEN_HEIGHT) - wTy) / 2;               // Position verticale de la fenetre

static bool filDeFer = false;
static bool animation = false;
static bool isMouse = false;
static bool firstPerson = false;
static bool lumiere = true;
static bool mort = false;
static bool lockCam = true;
static bool depassement = false;
static bool tire = false;
static bool fullScreen = false;
static int nbTire = 0;
static float posXTir = 0;
static float posYTir = 0;



static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };

static int rz = 0;
static int mouseX = 0;
static bool touches[] = { false, false, false, false };

static float speedAnneauZ = 0.3f;
static float speedDeplacement = 0.9f;

static bool texture = true;
static unsigned int textureID[3] = { 0,0,0 };

//std::chrono::time_point<std::chrono::system_clock> timeStart = std::chrono::system_clock::now();

Hud hud;
Vaisseau v;
Skybox skybox;
Patatoide patatoides[NBPATATOIDE];
Anneau anneaux[NBANNEAU];
Laser l[3];


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

static void initPatatoides(bool reset) {
    for (int i = 0; i < NBPATATOIDE; i++) {
        patatoides[i].setAngleRotation(static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 360.0)));
        float sommeAxe = 0.0f;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        do {
            x = ((float)(1 + (rand() % 2))) - 1;
            y = ((float)(1 + (rand() % 2))) - 1;
            z = ((float)(1 + (rand() % 2))) - 1;
            sommeAxe = x + y + z;
        } while (sommeAxe == 0.0);
        patatoides[i].setAxeRotationX(x);
        patatoides[i].setAxeRotationY(y);
        patatoides[i].setAxeRotationZ(z);
        patatoides[i].setDirection((-1 + (rand() % 3)));
        patatoides[i].setSpeed(static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 0.4)) + 0.05);
        patatoides[i].setSpeedRotation(static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 2.0)));
        float nPosPatatoidesX;
        if (patatoides[i].getDirection() == -1) {
            nPosPatatoidesX = 35.0f;
        }
        else if (patatoides[i].getDirection() == 1) {
            nPosPatatoidesX = -35.0f;
        }
        else {
            nPosPatatoidesX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
        }
         
        float nPosPatatoidesY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 30.0)) - 15.0;
        float nPosPatatoidesZ = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / -90.0)) - 15.0;
        
        patatoides[i].setPosX(nPosPatatoidesX);
        patatoides[i].setPosY(nPosPatatoidesY);
        patatoides[i].setPosZ(nPosPatatoidesZ);
        if(!reset)patatoides[i].chargementTexture("textureAsteroide.png", textureID[1]);
        patatoides[i].texture = textureID[1];
    }
}

static void initLaser() {
    for (int i = 0; i < 3; i++) {
        l[i] = Laser(v, i);
    }
}

static void init(void) {
    const GLfloat shininess[] = { 128.0 };
    const GLfloat pos[] = {70.0F, 20.0F, 10.0F, 0.0F};
    const GLfloat pos1[] = { v.getPosX() + 20.0F, 0.0F, 10.0F, 0.0F };
    const GLfloat pos2[] = { v.getPosX() - 20.0F, 0.0F, 10.0F, 0.0F };
    const GLfloat pos3[] = { 0.0F, v.getPosY() + 20.0F, 10.0F, 0.0F };
    const GLfloat pos4[] = { 0.0F, v.getPosY() - 20.0F, 10.0F, 0.0F };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, blanc);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glGenTextures(3, textureID);
    
    v = Vaisseau(1.0f);
    v.chargementTexture("textureVaisseau.png", textureID[0]);
    v.texture = textureID[0];
    initLaser();
    srand((unsigned int)time(0));
    initAnneaux();
    initPatatoides(false);
    skybox.chargementTexture("space.png", textureID[2]);
}

static void initSkybox() {
    int rx, ry;
}

/* Scene dessinee                               */

static void scene(void) {

    glPushMatrix();
    for (int i = 0; i < NBPATATOIDE; i++) {
        if(!patatoides[i].isBoomed()){
            glPushMatrix();
            glTranslatef(patatoides[i].getPosX(), patatoides[i].getPosY(), patatoides[i].getPosZ());
            glRotatef(patatoides[i].getAngleRotation(), patatoides[i].getAxeRotationX(), patatoides[i].getAxeRotationY(), patatoides[i].getAxeRotationZ());
            patatoides[i].myPatatoide(1.0f);
            glPopMatrix();
        }
    }

    for (int i = 0; i < NBANNEAU; i++) {
        glPushMatrix();
        glTranslatef(anneaux[i].getPosX(), anneaux[i].getPosY(), anneaux[i].getPosZ());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, jaune);
        anneaux[i].myPrecious(0.1, 3.0, 18, 72);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(v.getPosX(), v.getPosY(), v.getPosZ());
    v.mySolidSpaceShip();
    glPopMatrix();

    int nbLaser = v.getVie();
    if (tire) {
        nbLaser = nbTire;
    }
    for (int i = 0; i < nbLaser; i++) {
        glPushMatrix();
        float setX = v.getPosX() + v.coordCanons[i][0];
        float setY = v.getPosY() + v.coordCanons[i][1];
        if (tire) {
            setX = posXTir + v.coordCanons[i][0];
            setY = posYTir + v.coordCanons[i][1];
        }
        l[i].setPosX(setX);
        l[i].setPosY(setY);
        glTranslatef(l[i].getPosX(), l[i].getPosY(), l[i].getPosZ());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
        l[i].mySolidLaser();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);
        glPopMatrix();
    }
    
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    skybox.drawSkyBox(0.0f, 0.0f);
    glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_CUBE_MAP_ARB);
    glEnable(GL_LIGHTING);
    if (lumiere) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }

    /*const GLfloat light0_position[] = { v.getPosX(),v.getPosY(),v.getPosZ(),1.0 };
    const GLfloat light1_position[] = { 0.0,0.0,0.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };*/
    //glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, blanc);
    //glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    //glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glPushMatrix();


    float cameraPosX = firstPerson ? v.getPosX() : v.getPosX();
    float cameraPosY = firstPerson ? v.getPosY() : v.getPosY() + 4.0;
    float cameraPosZ = firstPerson ? v.getPosZ() -2.0 : v.getPosZ() + 12.0;

    float cameraLookX = firstPerson ? v.getPosX() : v.getPosX();
    float cameraLookY = firstPerson ? v.getPosY() : v.getPosY();
    float cameraLookZ = firstPerson ? v.getPosZ() - 3.0 : -(v.getPosZ() - 0.1);

    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, cameraLookX, cameraLookY, cameraLookZ, 0.0, 1.0, 1.0);
    
    if (filDeFer)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (!lockCam && !firstPerson) {
        glRotatef(rz, 0, 1.0, 0);
    }
    
    scene();

    if (depassement && !mort) {
        hud.drawHud("Vous sortez de la zone de jeu, revenez vers le centre", -1000, -2.5, 8.0);
    }
    if (!animation && !mort)
        hud.drawHud("Pour lancer le parcours, appuyer sur [entree] !",-1000,-2.5,8.0);

    if (mort)
        hud.drawHud("Vous etes decede, pour relancer la partie appuyez sur [r] ", -1000, -2.5, 8.0);

    
    hud.drawHud("score", v.getScore(), -8.0, 8.0);
    hud.drawHud("vie", v.getVie(), 8.0, 8.0);


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
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0F, (float)wx / wy, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
    if (tire) {
        for (int i = 0; i < 3; i++) {
            l[i].setPosZ(l[i].getPosZ() - 0.1);
        }
        if (l[0].getPosZ() < -40.0f) {
            initLaser();
            tire = false;
        }
    }

    if (v.getScore() % 5 == 0 && v.getScore() != 0) {
        speedAnneauZ += 0.003;
        speedDeplacement += 0.003;
    }

    for (int i = 0; i < NBANNEAU; i++) {
        if (anneaux[i].getPosZ() > 6.0f)
        {
            anneaux[i].setPosZ(-(NBANNEAU * 30.0));

            float nPosAnneauX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
            float nPosAnneauY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
            anneaux[i].setPosX(nPosAnneauX);
            anneaux[i].setPosY(nPosAnneauY);

            anneaux[i].unMiam();
        }
        else {

            anneaux[i].setPosZ(anneaux[i].getPosZ()+speedAnneauZ);
        }

        if (v.miamAnneau(anneaux[i])) {
            anneaux[i].miam();
        }

    }

    for (int i = 0; i < NBPATATOIDE; i++) {

        patatoides[i].setAngleRotation(patatoides[i].getAngleRotation() + patatoides[i].getSpeedRotation());
        if (patatoides[i].getPosZ() > 6.0f)
        {
            patatoides[i].setPosZ(static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / -90.0)) - 15.0);

            float nPosPatatoideX;
            if (patatoides[i].getDirection() == -1) {
                nPosPatatoideX = 35.0f;
            }
            else if (patatoides[i].getDirection() == 1) {
                nPosPatatoideX = -35.0f;
            }
            else {
                nPosPatatoideX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
                patatoides[i].setPosZ(-(NBANNEAU * 30));
            }
            float nPosPatatoideY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 30.0)) - 15.0;
            patatoides[i].setPosX(nPosPatatoideX);
            patatoides[i].setPosY(nPosPatatoideY);

            patatoides[i].deBoom();
        }
        else {

            patatoides[i].setPosZ(patatoides[i].getPosZ() + patatoides[i].getSpeed());
        }

        if (patatoides[i].getPosX() < -40.0f || patatoides[i].getPosX() > 40.0f)
        {
            patatoides[i].setPosZ(static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / -90.0)) - 15.0);

            float nPosPatatoideX;
            if (patatoides[i].getDirection() == -1) {
                nPosPatatoideX = 35.0f;
            }
            else if (patatoides[i].getDirection() == 1) {
                nPosPatatoideX = -35.0f;
            }
            else {
                nPosPatatoideX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
                patatoides[i].setPosZ(-(NBANNEAU * 30));
            }
            float nPosPatatoideY = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 30.0)) - 15.0;
            patatoides[i].setPosX(nPosPatatoideX);
            patatoides[i].setPosY(nPosPatatoideY);

            patatoides[i].deBoom();
        }
        else {

            patatoides[i].setPosZ(patatoides[i].getPosZ() + patatoides[i].getSpeed());
            if (patatoides[i].getDirection() == 1) {
                patatoides[i].setPosX(patatoides[i].getPosX() + patatoides[i].getSpeed());
            }
            else if (patatoides[i].getDirection() == -1) {
                patatoides[i].setPosX(patatoides[i].getPosX() - patatoides[i].getSpeed());
            }          
        }

        if (v.enCollision(patatoides[i])) {
            patatoides[i].boom();
        }

        if (tire) {
            for (int j = 0; j < 3; j++) {
                if (l[j].enCollision(patatoides[i])) {
                    patatoides[i].boom();
                }
            }
        }
        
        if (v.getVie() <= 0) {
            mort = true;
            animation = false;
            glutIdleFunc(NULL);
            
        }
    }
    

    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 0x1B:
        exit(0);
        break;
    case 0x20:
        filDeFer = !filDeFer;
        glutPostRedisplay();
        break;
    case 0xd:
        if (mort)return;
        animation = !animation;
        if (animation)
            glutIdleFunc(idle);
        else
            glutIdleFunc(NULL);
        glutPostRedisplay();
        break;
    case 'r':
        v.reset();
        initAnneaux();
        initPatatoides(true);
        initLaser();
        animation = false;
        mort = false;
        tire = false;
        depassement = false;
        speedAnneauZ = 0.3f;
        speedDeplacement = 0.9f;
        glutIdleFunc(NULL);
        glutPostRedisplay();
        break;
    case 'f':
        tire = true;
        nbTire = v.getVie();
        posXTir = v.getPosX();
        posYTir = v.getPosY();
        glutPostRedisplay();
        break;
    }
}

static void deplacement() {

    if (mort || !animation) return;

    if (v.getPosX() <= -15.0f || v.getPosX() >= 15.0f || v.getPosY() <= -10.0f || v.getPosY() >= 10.0f) {
        depassement = true;
    }
    else {
        depassement = false;
    }

    if (touches[0] && v.getPosX() >= -15.0f) {   //Gauche
        v.setPosX(v.getPosX() - speedDeplacement);
    }
    if (touches[1] && v.getPosX() <= 15.0f) {   //Droite
        v.setPosX(v.getPosX() + speedDeplacement);
    }
    if (touches[2] && v.getPosY() <= 10.0f) {   //Haut
        v.setPosY(v.getPosY() + speedDeplacement);
    }
    if (touches[3] && v.getPosY() >= -10.0f) {   //Bas
        v.setPosY(v.getPosY() - speedDeplacement);
    }   
    
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
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
    case GLUT_KEY_F4:
        lockCam = !lockCam;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F5:
        if (!fullScreen)
        {
            glutFullScreen();
            fullScreen = true;
        }
        else {
            glutPositionWindow(wPx, wPy);
            glutReshapeWindow(1280, 720);
            fullScreen = false;
        }
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
    //printf("M  %4d %4d %4d %4d\n", button, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    if (!lockCam && !firstPerson) {
        rz += (mouseX - x);
        mouseX = x;
        glutPostRedisplay();
    }
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x, int y) {
    printf("PM %4d %4d\n", x, y);
}

/* Fonction ex�cut�e automatiquement            */
/* lors de l'ex�cution de la fonction exit()    */

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
    glutCreateWindow("La Traversée des Anneaux");
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
