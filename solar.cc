#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>


using namespace std;
double xVal=250;
double yVal=0;
double zVal=0;
float earthRotation;
bool showText = false;
bool showPluto = false;
bool paused = false;

float buttonPositions[8][2];
float buttonColors[8][3] = {{0, 0, 0},
{0, 0, 0.5},
{0, 0.5, 0},
{0, 0.5, 0.5},
{0.5, 0, 0},
{0.5, 0, 0.5},
{0.5, 0.5, 0},
{0.5, 0.5, 0.5}
};

float speed = 0.1;
double sunRadius = 5.0;
GLfloat sunPosition[] = {0.0,0.0,0.0,1.0};

void writeText(float x, float y, char const* text, void* font){
	int l=strlen( text );
	glRasterPos2f( x, y);
	for(int  i=0; i < l; i++)
	{
		glutBitmapCharacter(font, text[i]); 
	}
}

void drawTextOnPlanet(char* text){
	glDisable (GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);
	glRasterPos2i( 0, 0);
	writeText(0,0, text, GLUT_BITMAP_TIMES_ROMAN_10);
	glEnable (GL_LIGHTING);
	glEnable (GL_DEPTH_TEST);
}


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
	if(showText)
	{
		char earthText[32] = "Mercury";
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();

	//Venus

	glPushMatrix(); 
	glColor3f(0.9,0.7,0.1);
	glRotated(earthRotation * 1.62 * speed, 0, 1, 0);
	glTranslated(0,0,-30);
	gluSphere(quad, 1, 20, 20);
	if(showText)
	{
		char earthText[32] = "Venus"; //to do: change name to planetText or something.
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();

	//Earth
	glPushMatrix(); 
	glColor3f(0.0,0.3,1.0);
	glRotated(earthRotation * speed, 0, 1, 0);
	glTranslated(0,0,-40);
	gluSphere(quad, 1, 20, 20);
	if(showText)
	{
		char earthText[32] = "Earth";
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();

	//Mars
	glPushMatrix(); 
	glColor3f(1.0,0.0,0.0);
	glRotated(earthRotation * 0.531 * speed, 0, 1, 0);
	glTranslated(0,0,-50); 
	gluSphere(quad, 1, 20, 20);
	if(showText)
	{
		char earthText[32] = "Mars";
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();


	//Jupiter
	glPushMatrix(); 
	glColor3f(1.0,1.0,0.0);
	glRotated(earthRotation * 0.083 * speed, 0, 1, 0);
	glTranslated(0,0,-60); 
	gluSphere(quad, 3, 20, 20);
	if(showText)
	{
		char earthText[32] = "Jupiter";
		drawTextOnPlanet(earthText);
	}
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
	if(showText)
	{
		char earthText[32] = "Saturn";
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();

	//Uranus
	glPushMatrix();
	glColor3f(0.9,0.9,0.9);
	glRotated(earthRotation * 0.0119 * speed, 0, 1, 0);
	glTranslated(0,0,-80); 
	gluSphere(quad, 1, 20, 20);
	if(showText)
	{
		char earthText[32] = "Uranus";
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();

	//Neptune
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.9);
	glRotated(earthRotation * 0.00606 * speed, 0, 1, 0);
	glTranslated(0,0,-90); 
	gluSphere(quad, 1, 20, 20);
	if(showText)
	{
		char earthText[32] = "Neptune";
		drawTextOnPlanet(earthText);
	}
	glPopMatrix();

	if (showPluto)
	{
		//Pluto
		glPushMatrix(); 
		glColor3f(0.9,0.5,0.9);
		glRotated(earthRotation * 0.00403 * speed, 0, 1, 0);
		glTranslated(0,0,-100); 
		gluSphere(quad, 1, 20, 20);
		if(showText)
		{
			char earthText[32] = "Pluto";
			drawTextOnPlanet(earthText);
		}
		glPopMatrix();
	}

	glPopMatrix();
	if(!paused)
		earthRotation++;
	glutPostRedisplay();
   	glutSwapBuffers();
   	glFlush();
	
}



void drawRectangle(float x, float y, float width, float height)
{
	glBegin(GL_POLYGON);
  	glVertex3f(x, y, 0.0);
  	glVertex3f(x, y + height, 0.0);
  	glVertex3f(x + width, y + height, 0.0);
  	glVertex3f(x + width, y, 0.0);
 	glEnd();

}

void init2(void) 
{

   glLoadIdentity();
   glClear (GL_COLOR_BUFFER_BIT );
	for(int i = 0; i < 8; i++)
	{
	buttonPositions[i][0] = floor(i/4) - 1; 
	buttonPositions[i][1] = 0.5 - ((i) % 4) * 0.5 ;
	}


}

void reshape2 (int w, int h)
{

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
}

void display2(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	string buttonText[8] = {"Top View", "Side View", "Isometric View", "Display Names", "Pluto", "6", "Speed Up", "Pause/Play"};

	for(int i = 0; i < 8; i++)
	{
		char *name = NULL;
		//strcpy(name, buttonText[i].c_str());
		glColor3f(buttonColors[i][0], buttonColors[i][1], buttonColors[i][2]);
		drawRectangle(buttonPositions[i][0],buttonPositions[i][1],1,0.5);
		glColor3f(1, 1, 1);
		writeText(buttonPositions[i][0], buttonPositions[i][1], buttonText[i].c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
	}

	glFlush();
	glutPostRedisplay();
   	

}

int getButtonHit(float x, float y){
	for(int i = 0; i < 8; i++)
	{
		if(x > buttonPositions[i][0] && x < buttonPositions[i][0] + 1 && y > buttonPositions[i][1] && y < buttonPositions[i][1] + 0.5)
		{
			return i;
		}
	}
	return -1;
}


// to do: add speed up, slow down, show text, and pluto buttons
void mouse2(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		//convert to coordinate number range.
		float newX = (((x) * (2)) / (500.0)) + -1;
		float newY = ((((y) * (2)) / (500.0)) + -1) * -1;
		switch(getButtonHit(newX, newY))
		{
			case 0:
			xVal = 0;
			yVal = 300;
			zVal = 0;
			break;
			case 1:
			xVal = 0;
			yVal = 0;
			zVal = 255;
			break;
			case 2:
			xVal = 100;
			yVal = 100;
			zVal = 100;
			break;
			case 3:
			showText = !showText;
			break;
			case 4:
			showPluto = !showPluto;
			break;
			case 5:
			paused = !paused;
			break;
			case 6:
			speed += 0.1;
			break;
			case 7:
			if(speed > 0)
				speed -= 0.1;
			break;
		}
	}
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
   	glutInitWindowPosition (200, 100);
	init();

	glutCreateWindow ("Solar System");
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);


	glutInitWindowPosition (700, 100);
	init2();
	glutCreateWindow ("Options");

	glutDisplayFunc(display2); 
	glutReshapeFunc(reshape2);
	glutMouseFunc(mouse2);

	glutMainLoop();

   	return 0;
}

