#include <stdio.h>
#include "Light.hpp"
#include "Matrix.hpp"


Light::Light(){
	x=1.5;
	y=1.5;
	z=1.5;

	//light and shading
	I = 4.0f;  //point light intensity
	Rd = 0.5; //diffusion reflection coefficient
	Ia = 1.0; //ambient light intensity
	Ra = 0.5; //ambient reflection coefficient
	Size = 30;
	On = true;

	GLfloat light0_ambient[] = {Ia, Ia, Ia, 10.0};
	GLfloat light0_diffuse[] = {I, I, I, 1.5};
	GLfloat light0_position[] = {x, y, z, 0.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

}
void Light::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle){ //w.r.p.t WC
    Matrix *m =  new Matrix();
    m->rotate(rx, ry, rz, angle);
    GLfloat vector[4];
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = 1;
    m->multiply_vector(vector);
    x = vector[0];
    y = vector[1];
    z = vector[2];
}

void Light::Increment(GLfloat pointLight, GLfloat diffusion, GLfloat ambientLight,  GLfloat ambientReflect){
	I+=pointLight;
	Rd+=diffusion;

	Ia+=ambientLight;
	Ra+=ambientReflect;

	if (I < 0) I = 0;  if (I > 10 ) I = 10;
	if (Rd < 0) Rd = 0;  if (Rd > 1 ) Rd = 1;

	if (Ia < 0) Ia = 0;  if (Ia > 1 ) Ia = 1;
	if (Ra < 0) Ra = 0;  if (Ra > 1 ) Ra = 1;

	GLfloat light0_ambient[] = {Ia, Ia, Ia, 1.0};
	GLfloat light0_diffuse[] = {I, I, I, 1.5};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

}
//Draw point light
void Light::Draw(){

	if(On){
		glPushMatrix();

		//glColor3f(I, I, I);
		GLfloat pos[] = {x,y,z};

		glEnable(GL_POINT_SMOOTH);
		//glPointSize(Size);

		glBegin(GL_POINTS);
			glVertex3fv(&pos[0]);
		glEnd();

		glPopMatrix();
	}
}

void Light::translate(GLfloat tx, GLfloat ty, GLfloat tz){ //w.r.p.t WC
	x+=tx;
	y+=ty;
	z+=tz;
	GLfloat light_position[] = {x,y,z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

