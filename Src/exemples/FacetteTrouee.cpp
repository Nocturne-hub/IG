/* Une facette carree trouee d'un trou carre    */
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

static float rx = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe x
static float sens = 1.0F;          // Sens de rotation de la scene sur elle-meme autour de l'axe x
static float ry = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe y
static float rz = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe z
static int anim = 0;               // Flag d'activation/desactivation de l'animation
static int pMode = 1;              // Flag de switch entre modes d'affichage wireframe et fill 
static int mouseActive = 0;        // Flag de d'indication que la souris est active (bouton presse) ou non 
static int mouseX = 0;             // Derniere position en x relevee pour la souris

static int wTx = 250;              // Resolution horizontale de la fenetre
static int wTy = 250;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre

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

//////////////////////////////////////////////////

/* Scene dessinee                               */

static void scene(void) {
  glPushMatrix();
  glBegin(GL_QUAD_STRIP);
  glVertex3f(-1.0F,-1.0F, 0.0F);
  glVertex3f( 0.0F,-0.5F, 0.0F);
  glVertex3f(-1.0F, 1.0F, 0.0F);
  glVertex3f(-0.5F ,0.0F, 0.0F);
  glVertex3f( 1.0F, 1.0F, 0.0F);
  glVertex3f( 0.0F, 0.5F, 0.0F);
  glVertex3f( 1.0F,-1.0F, 0.0F);
  glVertex3f( 0.5F, 0.0F, 0.0F);
  glVertex3f(-1.0F,-1.0F, 0.0F);
  glVertex3f( 0.0F,-0.5F, 0.0F);
  glEnd();
  glPopMatrix();
}

//////////////////////////////////////////////////

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
  glPolygonMode(GL_FRONT_AND_BACK,(pMode == 1) ? GL_FILL : GL_LINE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(rz,0.0F,0.0F,1.0F);
  glRotatef(rx,1.0F,0.0F,0.0F);
  glRotatef(ry,0.0F,1.0F,0.0F);
  glScalef(0.8F,0.8F,0.8F);
  scene();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
    printf("Attention erreur %d\n",error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double ratio =(double) wx/wy; 
  if ( wx > wy ) 
    glOrtho(-ratio,ratio,-1.0,1.0,-1.0,1.0);
    else
    glOrtho(-1.0,1.0,-1.0/ratio,1.0/ratio,-1.0,1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
  rx += sens;
  glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
  switch (key) {
    case 0x0D :
      { anim = !anim;
        glutIdleFunc(( anim ) ? idle : NULL); }
      break;
    case ' ' :
      { pMode = !pMode;
        glutPostRedisplay(); }
      break;
    case 0x1B :
      exit(0);
      break; }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
  switch(specialKey) {
    case GLUT_KEY_RIGHT :
      ry += 1.0F;
      glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT :
      ry -= 1.0F;
      glutPostRedisplay();
      break; }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button,int state,int x,int y) {
  if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) ) {
    mouseX = x;
    mouseActive = 1; }
  if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_UP ) ) {
    mouseActive = 0; }
  if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_UP ) )
    sens *= -1.0F;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x,int y) {
  if ( mouseActive ) {
    rz += (mouseX - x);
    mouseX = x;
    glutPostRedisplay(); }
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x,int y) {
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
  glutCreateWindow("Une facette carrée trouée d'un trou carré");
  init();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  //glutPassiveMotionFunc(passiveMouseMotion);
  glutReshapeFunc(reshape);
  //glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
