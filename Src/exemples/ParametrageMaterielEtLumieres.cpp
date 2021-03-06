/* Materiel et lumieres                         */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Fevrier 2021                                 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Constantes globales                          */

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float gris[] = { 0.5F,0.5F,0.5F,1.0F };
static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };

static const GLfloat posLum0[] = { 2.0,2.0,2.0,1.0 };
static const GLfloat posLum1[] = { -2.0,0.0,4.0,0.0 };
static const GLfloat posLum2[] = { -3.0,-3.0,15.0,1.0 };
static const GLfloat posLum3[] = { 0.0,0.0,0.0,1.0 };

static const GLfloat difLum0[] = { 1.0,0.0,0.0,1.0 };
static const GLfloat difLum1[] = { 0.0,1.0,0.0,1.0 };
static const GLfloat difLum2[] = { 0.0,0.0,1.0,1.0 };

static const GLfloat ambLum3[] = {1.0,0.0,1.0,1.0 };

static const GLfloat speLum1[] = { 1.0,1.0,1.0,1.0 };
static const GLfloat speLum2[] = { 1.0,1.0,0.0,1.0 };

static const GLfloat spotDirection[] = { 3.0,3.0,-10.0 };


/* Variables globales                           */

static int cFond = 0;              // Numero de la couleur de fond (0: gris, 1: blanc, 2:noir)
static float r1 = 0.0F;            // Angle de rotation de la scene sur elle-meme
static float r2 = 0.0F;            // Angle de rotation de la scene sur elle-meme
static int anim = 1;               // Flag d'action/desactivation de l'animation
static int pMode = 1;              // Flag de switch entre modes d'affichage wireframe et fill 
static int wTx = 640;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre
static double sz = 0.5;            // Taille facettes
static const GLfloat angle = 40.0;
static bool f3 = false;
/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
  const GLfloat shininess[] = { 50.0 };
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);


}

/* Scene dessinee                               */

static void solidSphere(double rayon,double hauteur,double sz) {
  int n =(int) (rayon*2*3.14159/sz);
  if ( n < 3)
	n = 3;
  int m =(int) (hauteur/2.0*3.14159/sz);
  if ( m < 3)
	m = 3;
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0F);
  glScalef(rayon,rayon,hauteur/2.0);
  glutSolidSphere(1.0,n,m);
  glPopMatrix();
}

static void element() {
  glPushMatrix();
  glTranslatef(-5.0F,0.0F,5.0F);
  solidSphere(1.5,20.0,sz);
  for ( int i = 0 ; i < 2 ; i++ ) {
	glTranslatef(0.0F,5.0F,0.0F);
	solidSphere(2.5,5.0,sz);
	glRotatef(-90.0F,0.0F,0.0F,1.0F);
	glTranslatef(0.0F,5.0F,0.0F);
	solidSphere(1.5,20.0,sz);
  }
  glPopMatrix();
}

static void scene() {
  glPushMatrix();
  for ( int i = 0 ; i < 4 ; i++ ) {
	glPushMatrix();
	glRotatef(90.0F*i,1.0F,0.0F,0.0F);
	element();
	glPopMatrix();
  }
  glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
  const float *fond;
  switch (cFond) {
	case 0 :
	  fond = gris;
	  break;
	case 1 :
	  fond = blanc;
	  break;
	case 2 :
	  fond = noir;
	  break; }
  glClearColor(fond[0],fond[1],fond[2],fond[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK,(pMode == 1) ? GL_FILL : GL_LINE);
  glPushMatrix();

  glLightfv(GL_LIGHT0, GL_DIFFUSE, difLum0);
  glLightfv(GL_LIGHT0, GL_POSITION, posLum0);
 

  glLightfv(GL_LIGHT1, GL_POSITION, posLum1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, difLum1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, speLum1);

  glLightfv(GL_LIGHT2, GL_POSITION, posLum2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, difLum2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, speLum2);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
  glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, &angle);

  glLightfv(GL_LIGHT3, GL_POSITION, posLum3);
  glLightfv(GL_LIGHT3, GL_AMBIENT, ambLum3);

  glRotatef(r1,1.0F,2.0F,3.0F);
  glRotatef(r2,-1.0F,2.0F,-3.0F);
  scene();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
	printf("Attention erreur %d\n",error);
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
  r1 += 1.1355F;
  r2 += 0.6755F;
  glutPostRedisplay();
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if ( wy < wx )
	gluPerspective(80.0,(double) wx/wy,20.0-15.0,20.0+15.0);
	else
	gluPerspective(80.0*((double) wy/wx),(double) wx/wy,20.0-15.0,20.0+15.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0,0.0,20.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
  switch (key) {
	case 43 :
	  sz /= 1.01;
	  glutPostRedisplay(); 
	  break;
	case 45 :
	  sz *= 1.01;
	  glutPostRedisplay(); 
	  break;
	case 'a' :
	  { anim = !anim;
		glutIdleFunc(( anim ) ? idle : NULL); }
	  break;
	case 'z' :
	  { pMode = !pMode;
		glutPostRedisplay(); }
	  break;
	case 'f' :
	  { cFond = (cFond+1)%3;
		glutPostRedisplay(); }
	  break;
	case 'F' :
	  { static int full = 0;
		static int wFx;
		static int wFy;
		full = !full;
		if ( full ) {
		  wFx = glutGet(GLUT_WINDOW_WIDTH);
		  wFy = glutGet(GLUT_WINDOW_HEIGHT);
		  wPx = glutGet(GLUT_WINDOW_X);
		  wPy = glutGet(GLUT_WINDOW_Y);
		  glutFullScreen(); }
		  else {
		  glutPositionWindow(wPx,wPy);
		  glutReshapeWindow(wFx,wFy); } }
	  break;
	case 0xd :
		glIsEnabled(GL_LIGHTING) ? glDisable(GL_LIGHTING) : glEnable(GL_LIGHTING);
		glutPostRedisplay();
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
	case GLUT_KEY_UP :
	  r1 += 1.0F;
	  glutPostRedisplay();
	  break;
	case GLUT_KEY_DOWN :
	  r1 -= 1.0F;
	  glutPostRedisplay();
	  break;
	case GLUT_KEY_RIGHT :
	  r2 += 1.0F;
	  glutPostRedisplay();
	  break;
	case GLUT_KEY_LEFT :
	  r2 -= 1.0F;
	  glutPostRedisplay();
	  break;
	case GLUT_KEY_F1 :
		glIsEnabled(GL_LIGHT0) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:
		glIsEnabled(GL_LIGHT1) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_F3:
		glIsEnabled(GL_LIGHT2) ? glDisable(GL_LIGHT2) : glEnable(GL_LIGHT2);
		glutPostRedisplay();
		break;
	case GLUT_KEY_F4:
		glIsEnabled(GL_LIGHT3) ? glDisable(GL_LIGHT3) : glEnable(GL_LIGHT3);
		glutPostRedisplay();
		break;

  }
}

/* Fonction principale                          */

int main(int argc,char **argv) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wTx,wTy);
  glutInitWindowPosition(wPx,wPy);
  glutCreateWindow("Materiel et lumi?res");
  init();
  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc((anim) ? idle : NULL);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
