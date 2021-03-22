/* Fonctionnement de GLUt                       */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Janvier 2019                                 */

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables globales                           */

static int wTx = 480;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre
static bool filDeFer = false;
static float angle = 0.0;
static bool animation = true;
static bool gauche = true;
static bool isMouse = false;

static int rz = 0;
static int mouseX = 0;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

/* Scene dessinee                               */

void mySolidCube(double c) {
    glPushMatrix();
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

    glNormal3f(-1.0, 0,0.0);
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
    glPopMatrix();
}



static void scene(void) {
  
  mySolidCube(1.0);
 
}



/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    int rotate = gauche ? -1.0 : 1.0;

 // printf("D\n");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
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
  if ( error != GL_NO_ERROR )
    printf("Attention erreur %d\n",error);
}

/* Fonction executee lors d'un changeme nt       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  printf("R\n");
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
  angle += 0.1f;
  glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
  printf("K  %4c %4d %4d\n",key,x,y);
  switch (key) {
    case 0x1B :
      exit(0);
      break;
    case 0x20 :
        printf("espace");
        filDeFer = !filDeFer;
        glutPostRedisplay();
        break;
    case 0xd :
        printf("entree");
        animation = !animation;
        if(animation)
            glutIdleFunc(idle);
        else
            glutIdleFunc(NULL);
        glutPostRedisplay();
        break;
  }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
  printf("S  %4d %4d %4d\n",specialKey,x,y);
  switch (specialKey) {
    case 0x64 :
        printf("gauche");
        gauche = true;
        glutPostRedisplay();
        break;
    case 0x66:
        printf("droite");
        gauche = false;
        glutPostRedisplay();
        break;
  }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button,int state,int x,int y) {
  printf("M  %4d %4d %4d %4d\n",button,state,x,y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x,int y) {
  printf("MM %4d %4d\n",x,y);
  rz += (mouseX - x);
  mouseX = x;
  glutPostRedisplay();

}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x,int y) {
  printf("PM %4d %4d\n",x,y);
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
  printf("Bye\n");
}

/* Fonction principale                          */

int main(int argc,char **argv) {

  atexit(clean);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wTx,wTy);
  glutInitWindowPosition(wPx,wPy);
  glutCreateWindow("Gestion événementielle de GLUt");
  init();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  //glutPassiveMotionFunc(passiveMouseMotion);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
