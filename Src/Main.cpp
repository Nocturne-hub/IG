#include "Vaisseau.h"
#include "Patatoide.h"
#include "Anneau.h"
#include <time.h>
#include <iostream>

#define PI 3.1415926535898


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

static float posAnneauX = 0.0;
static float posAnneauZ = -5.0;
static float speedAnneauZ = 0.1;

static bool texture = true;

static unsigned int textureID[3] = { 0,0,0 };


Anneau a;
Patatoide p;
Vaisseau v;


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

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
    p.chargementTexture("CAILLOU2.png", textureID[1]);
    p.texture = textureID[1];

    //sb.chargementTexture("Emoji3.png", textureID[2]);
    //sb.texture = textureID[2];
}




/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
        glPushMatrix();
            glTranslatef(v.getPosX(), v.getPosY(), v.getPosZ()-5.0);
            //glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
            p.myPatatoide(1.5f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(posAnneauX, 0.0f, posAnneauZ);
           // glMaterialfv(GL_FRONT, GL_DIFFUSE, jaune);
            a.myPrecious(0.1, 3.0, 18, 72);
        glPopMatrix();

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
    if (posAnneauZ > 6)
    {
        posAnneauZ = -10.0;
        //srand((unsigned int)time(NULL));
        posAnneauX = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 10.0)) - 5.0;
        printf("PosX = %f", posAnneauX);
    }
    else {
        posAnneauZ += speedAnneauZ;
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
        v.setPosX(v.getPosX() - 0.2f);
    }
    if (touches[1]) {
        v.setPosX(v.getPosX() + 0.2f);
    }
    if (touches[2]) {
        v.setPosY(v.getPosY() + 0.2f);
    }
    if (touches[3]) {
        v.setPosY(v.getPosY() - 0.2f);
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
