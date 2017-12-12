#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"


bool DEBUG = false;

Camera::Camera(){
	//position of camera
	eye.x = 7.0, eye.y = 4.0, eye.z = 7.0;
	ref.x = 3.0, ref.y = 2.0, ref.z = 3.0;
	viewup.x = 0.0,viewup.y = 1.0, viewup.z = 0.0;
	aspect = 1.0, viewAngle = 40.0, nearDist = 1.0, farDist = 100.0;
}


void Camera::setDefaultCamera(void) { // make default camera
	eye.x = 7.0, eye.y = 2.0, eye.z = 7.0;
	ref.x = 0.0, ref.y = 2.0, ref.z = 0.0;
	viewup.x = 0.0,viewup.y = 1.0, viewup.z = 0.0;
	aspect = 1.0, viewAngle = 40.0, nearDist = 1.0, farDist = 10.0;
}


void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, viewAngle = 40.0, nearDist = 1.0, farDist = 20.0;

}

void Camera::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){ //w.r.p.t WC

//	Matrix *m =  new Matrix();
//    m->rotate(rx, ry, rz, angle);
//
//    GLfloat vector[4];
//    vector[0] = eye.x;
//    vector[1] = eye.y;
//    vector[2] = eye.z;
//    vector[3] = 1;
//
//    m->multiply_vector(vector);

}
void Camera::turn(GLint dir){
	GLfloat speed = 0.02*dir;

    ref.z = (float)(eye.z + sin(speed)*(ref.x-eye.x) + cos(speed)*(ref.z-eye.z));
    ref.x = (float)(eye.x + cos(speed)*(ref.x-eye.x) + sin(speed)*(ref.z-eye.z));
}
void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz){ //w.r.p.t WC


	eye.x+=tx;
	eye.y+=ty;
	eye.z+=tz;

	//Project - I added these to rotate the entire matrix
	//ref.x+=tx;
	//ref.y+=ty;
	//ref.z+=tz;
}

void Camera::setProjectionMatrix() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z,
			  ref.x, ref.y, ref.z,
			  viewup.x,viewup.y,viewup.z);
}
void Camera::scene_2D(){

	 glClearColor(0.0, 0.0, 0.0, 0.0);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();

	 gluOrtho2D(0.0, 800.0, 0.0, 800.0);

	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
}

void Camera::scene_3D(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(viewAngle, aspect, nearDist, farDist);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
//	glClearDepth(1.0f);                   // Set background depth to farthest
//	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
//	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
//	glShadeModel(GL_SMOOTH);   // Enable smooth shading
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye.x, eye.y, eye.z,
			  ref.x, ref.y, ref.z,
			  viewup.x,viewup.y,viewup.z);
}
