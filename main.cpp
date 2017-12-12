#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "time.h"
#include "Maze.hpp"

GLint winWidth = 800, winHeight = 800;


//MODES
const int MODE_CREATE = 1;
const int MODE_BFS = 2;
GLint mode = MODE_CREATE;

//VIEW
const int VIEW_2D = 1;
const int VIEW_3D = 2;
GLint view = VIEW_2D;

//BFS
GLint isShading = 1;
extern GLint shadingType = 0;

GLint moving = 0, xBegin = 0,yBegin=0, type = 4;


//keyboard stuff
bool* keyStates = new bool[256];
bool* keySpecialStates = new bool[246];

//Declare a world containing all objects to draw.
World myWorld;
Camera myCamera;
Light myLight;
Maze myMaze;

//Keyboard Stuff
void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true;

	//PLACE START
	if (key=='q') {
    	GLint xx = x/(winWidth/myMaze.size);
    	GLint yy = y/(winHeight/myMaze.size);
		if(!myMaze.get(xx,yy)){
        	myMaze.start.x=xx;
        	myMaze.start.y=yy;
		}

	}
	//PLACE END
	if (key=='e') {
    	GLint xx = x/(winWidth/myMaze.size);
    	GLint yy = y/(winHeight/myMaze.size);
		if(!myMaze.get(xx,yy)){
        	myMaze.end.x=xx;
        	myMaze.end.y=yy;
        }

	}
	glutPostRedisplay();
}

void keyReleased (unsigned char key, int x, int y) {
	keyStates[key] = false;
	glutPostRedisplay();
}

void draw2DMaze(){
	int size=10;
	glBegin(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	for(float x = 0; x < winWidth; x += winWidth/size )
	{
	    glVertex3f(x, 0.0f, 0.0f);
	    glVertex3f(x, float(winHeight), 0.0f);
	}
	for( float y = 0; y < winHeight; y += winHeight/size )
	{
	    glVertex3f(0.0f, y, 0.0f);
	    glVertex3f(float(winWidth), y, 0.0f);
	}
	glEnd();
}


void display(void) {

	switch(view){

		case(VIEW_2D):{
			myCamera.scene_2D();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			draw2DMaze();
			myMaze.draw(winWidth, winHeight);

		} break;
	}
	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		myMaze.click(x,y,winWidth,winHeight);
	}
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	myCamera.setProjectionMatrix();
}
void timer(int){
	if(mode==MODE_BFS && !myMaze.done){
		myMaze.BFS();
		glutPostRedisplay();
		glutTimerFunc(300,timer,0);
	}

}

void mainMenu(GLint option) {
	switch (option) {
		//RESET
		case 1:{
			myMaze = Maze();
			mode=MODE_CREATE;
			view=VIEW_2D;
			myCamera.scene_2D();

		}break;
		//BFS
		case 2:{
			mode=MODE_BFS;
			myMaze.tiles.push(myMaze.start);
			glutTimerFunc(1,timer,0);
		}break;
		//QUIT
		case 4:{
			exit(0);
		}break;
	}
	glutPostRedisplay();
}
void initGL(){
	myCamera.scene_2D();
	view=VIEW_2D;
}
void menu() {
	//Different modes
	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddMenuEntry(" BFS", 2);
	glutAddMenuEntry(" Quit", 4);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Visualized Search Algorithm");

	menu();
	initGL();

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);

	glutDisplayFunc(display);
	glutMouseFunc(mouseAction);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
