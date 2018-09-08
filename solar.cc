#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

#define Nstep 1000000

using namespace std;
double xVal=0;
double yVal=255;
double zVal=0;
float earthRotation;

float speed = 0.1;
double sunRadius = 5.0;
GLfloat sunPosition[] = {0.0,0.0,0.0,1.0};

void Keyboard (unsigned char key, int x, int y) {  
    if(key=='q'||key=='Q')
        glutDestroyWindow(1);
    if(key=='a'||key=='A')
    {

        xVal=xVal+1;
        //std::cout<<xVal;
        glutPostRedisplay();


        glFlush ();
    }

    if(key=='d'||key=='D')
    {

        xVal=xVal-1;
        //std::cout<<xVal;
        glutPostRedisplay();
        


        glFlush ();
    }
    if(key=='w'||key=='W')
    {

        zVal=zVal-1;

        glutPostRedisplay();
       

        glFlush ();
    }

    if(key=='s'||key=='S')
    {

        zVal=zVal+1;

        glutPostRedisplay();
     


        glFlush ();
    }

if(key=='k'||key=='K')
    {

        yVal=yVal-1;

        glutPostRedisplay();

        glFlush ();
    }

if(key=='l'||key=='L')
    {

        yVal=yVal+1;

        glutPostRedisplay();
     
        glFlush ();
    }
}

void reshape (int w, int h)
{

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
   glMatrixMode(GL_MODELVIEW);
}


void display(){

	glPushMatrix ();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity(); 
	gluLookAt(xVal, yVal, zVal, 0, 0,-1, 0, 1, 0);

   	glEnable(GL_DEPTH_TEST);

	glColor3f(1.0,1.0,1.0);
	GLUquadric *quad;
	quad = gluNewQuadric();

	glDisable (GL_LIGHTING);

	//Sun
	gluSphere(quad, sunRadius, 20, 20);


	glLightfv (GL_LIGHT0, GL_POSITION, sunPosition);
	glEnable(GL_LIGHT0);
	glEnable (GL_LIGHTING);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;

	//Mercury

	glPushMatrix(); 
	glColor3f(0.6,0.6,0.6); //to do: replace with gl material stuff
	glRotated(earthRotation * 4.15 * speed, 0, 1, 0);
	glTranslated(0,0,-20); 
	gluSphere(quad, 1, 20, 20);
	glPopMatrix();

	//Venus

	glPushMatrix(); 
	glColor3f(0.9,0.7,0.1);
	glRotated(earthRotation * 1.62 * speed, 0, 1, 0);
	glTranslated(0,0,-30);
	gluSphere(quad, 1, 20, 20);
	glPopMatrix();



	//Earth
	glPushMatrix(); 
	glColor3f(0.0,0.3,1.0);
	glRotated(earthRotation * speed, 0, 1, 0);
	glTranslated(0,0,-40);
	gluSphere(quad, 1, 20, 20);
	glPopMatrix();

	//Mars
	glPushMatrix(); 
	glColor3f(1.0,0.0,0.0);
	glRotated(earthRotation * 0.531 * speed, 0, 1, 0);
	glTranslated(0,0,-50); 
	gluSphere(quad, 1, 20, 20);
	glPopMatrix();


	//Jupiter
	glPushMatrix(); 
	glColor3f(1.0,1.0,0.0);
	glRotated(earthRotation * 0.083 * speed, 0, 1, 0);
	glTranslated(0,0,-60); 
	gluSphere(quad, 3, 20, 20);
	glPopMatrix();

	//Saturn
	glPushMatrix(); 
	glColor3f(1.0,0.0,0.0);
	glRotated(earthRotation * 0.0344 * speed, 0, 1, 0);
	glTranslated(0,0,-70); 
	gluSphere(quad, 2, 20, 20);
	glColor3f(0.0,0.0,1.0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.3, 3, 20, 20);
	glPopMatrix();

	//Uranus
	glPushMatrix(); 
	glColor3f(0.9,0.9,0.9);
	glRotated(earthRotation * 0.0119 * speed, 0, 1, 0);
	glTranslated(0,0,-80); 
	gluSphere(quad, 1, 20, 20);
	glPopMatrix();

	//Neptune
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.9);
	glRotated(earthRotation * 0.00606 * speed, 0, 1, 0);
	glTranslated(0,0,-90); 
	gluSphere(quad, 1, 20, 20);
	glPopMatrix();

	

	glPopMatrix();
	earthRotation++;
	glutPostRedisplay();
	glFlush();

	
}

void init(){
   	//glClearColor (0.0, 0.0, 0.0, 0.0);
	//glLoadIdentity();
	//gluPerspective(40.0, (GLfloat) 500/(GLfloat) 500, 1.0, 100.0);

   	//glShadeModel (GL_SMOOTH);
   	//glEnable(GL_LIGHTING);
   	//glEnable(GL_LIGHT0);
   	//glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv){
   	glutInit(&argc, argv);
   	glutInitDisplayMode ( /*GLUT_DOUBLE |*/ GLUT_RGB | GLUT_DEPTH );

   	glutInitWindowSize (500, 500); 
   	glutInitWindowPosition (100, 100);
	init();
	glutCreateWindow ("Solar System");

	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);

	glutMainLoop();

   	return 0;
}

