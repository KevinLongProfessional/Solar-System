#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
//global variables.
double xVal=0;
double yVal=300;
double zVal=0;
float earthRotation;
bool showText = false;
bool showPluto = false;
bool paused = false;
GLUquadric *quad;
float speed;
double sunRadius = 5.0;
GLfloat sunPosition[] = {0.0,0.0,0.0,1.0};
float optionsHeight;
float optionsWidth;
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

void writeText(float x, float y, char const* text, void* font){
	int l=strlen( text );
	glRasterPos2f( x, y);
	for(int  i=0; i < l; i++)
	{
		glutBitmapCharacter(font, text[i]); 
	}
}

void drawTextOnPlanet(char const* text){
	glDisable (GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);
	glRasterPos2i( 0, 0);
	writeText(0,0, text, GLUT_BITMAP_TIMES_ROMAN_10);
	glEnable (GL_LIGHTING);		
	glEnable (GL_DEPTH_TEST);
}

void drawPlanet(float r, float g, float b, float size, float distance, float rotationRatio, const char* PlanetName)
{
	glPushMatrix(); 
	glColor3f(r,g,b);
	glRotated(earthRotation * rotationRatio, 0, 1, 0);
	glTranslated(0,0,distance * -1); 
	gluSphere(quad, size, 20, 20);
	if(showText)
	{
		drawTextOnPlanet(PlanetName);
	}
	glPopMatrix();
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
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity(); 
	gluLookAt(xVal, yVal, zVal, 0, 0, -1, 0, 1, 0);
	//glEnable (GL_DEPTH_TEST);

	glColor3f(1.0,1.0,1.0);
	
	quad = gluNewQuadric();

	glDisable (GL_LIGHTING);

	string planetNames[9] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

	//Sun
	gluSphere(quad, sunRadius, 20, 20);
	glLightfv (GL_LIGHT0, GL_POSITION, sunPosition);

	glEnable(GL_LIGHT0);
	glEnable (GL_LIGHTING);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;
	

	//Mercury
	drawPlanet(0.9, 0.7, 0.1, 1.0, 20.0, 4.15, planetNames[0].c_str());

	//Venus
	drawPlanet(0.9, 0.7, 0.1, 1.0, 30.0, 1.62, planetNames[1].c_str());

	//Earth
	drawPlanet(0.0, 0.3, 1.0, 1.0, 40.0, 1.0, planetNames[2].c_str());

	//Mars
	drawPlanet(1.0, 0.0, 0.0, 1.0, 50.0, 0.531, planetNames[3].c_str());


	//Jupiter;
	drawPlanet(1.0, 1.0, 0.0, 3.0, 60.0, 0.083, planetNames[4].c_str());

	//Saturn (coded manually to account for ring)
	glPushMatrix(); 
	glColor3f(1.0,0.5,0.0);
	glRotated(earthRotation * 0.0344, 0, 1, 0);
	glTranslated(0,0,-70); 
	gluSphere(quad, 2, 20, 20);

	glColor3f(0.9,0.5,0.0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.3, 3, 20, 20);
	if(showText)
	{
		drawTextOnPlanet(planetNames[5].c_str());
	}
	glPopMatrix();

	//Uranus
	drawPlanet(0.9, 0.9, 0.9, 1.0, 80.0, 0.0119, planetNames[6].c_str());

	//Neptune
	drawPlanet(0.0, 0.0, 0.9, 1.0, 90.0, 0.00606, planetNames[7].c_str());

	if (showPluto)
	{
		//Pluto
		drawPlanet(0.9, 0.5, 0.9, 1.0, 100.0, 0.00403, planetNames[8].c_str());
	}

	if(!paused){
		earthRotation+= speed;
	}

	glutPostRedisplay();
   	glutSwapBuffers();
   	glFlush();
}

void init(){
	speed = 0.1;
	glEnable (GL_DEPTH_TEST);
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

void initOptions(void) 
{
	glLoadIdentity();
	glClear (GL_COLOR_BUFFER_BIT );
	for(int i = 0; i < 8; i++)
	{
		buttonPositions[i][0] = floor(i/4) - 1; 
		buttonPositions[i][1] = 0.5 - ((i) % 4) * 0.5 ;
	}
}

void reshapeOptions (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	optionsWidth = w;
	optionsHeight = h;
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void displayOptions(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	string buttonText[8] = {"Top View", "Side View", "Isometric View", "Display Names", "Include Pluto", "Pause", "Speed Up", "Slow Down"};

	for(int i = 0; i < 8; i++)
	{
		char *name = NULL;
		//strcpy(name, buttonText[i].c_str());
		glColor3f(buttonColors[i][0], buttonColors[i][1], buttonColors[i][2]);
		drawRectangle(buttonPositions[i][0],buttonPositions[i][1],1,0.5);
		glColor3f(1, 1, 1);
		writeText(buttonPositions[i][0], buttonPositions[i][1] + 0.1, buttonText[i].c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
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
void mouseOptions(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		//convert pixel position to -1 to 1 number range.
		float newX = (((x) * (2)) / (optionsWidth)) + -1; //to do: use a variable instead of 500.
		float newY = ((((y) * (2)) / (optionsHeight)) + -1) * -1;

		//determine which button was pressed and respond accordingly.
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
			speed += 0.05;
			break;
			case 7:
			if(speed > 0.06)
			{
				speed -= 0.05;
			}
			break;
		}
	}
}

int main(int argc, char** argv){
   	glutInit(&argc, argv);
   	glutInitDisplayMode ( /*GLUT_DOUBLE |*/ GLUT_RGB | GLUT_DEPTH );

   	glutInitWindowSize (500, 500); 
   	glutInitWindowPosition (200, 100);
	glutCreateWindow ("Solar System");
	init();
	glutDisplayFunc(display);	 
	glutReshapeFunc(reshape);


	glutInitWindowPosition (700, 100);
	initOptions();
	glutCreateWindow ("Options");

	glutDisplayFunc(displayOptions); 
	glutReshapeFunc(reshapeOptions);
	glutMouseFunc(mouseOptions);

	glutMainLoop();

   	return 0;
}

