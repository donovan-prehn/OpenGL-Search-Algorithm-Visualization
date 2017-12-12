/*
 * House.cpp
 *
 *  Created on: Oct 21, 2017
 *      Author: dny
 */

#include "Sphere.hpp"

Sphere::Sphere(GLfloat rad, GLint stack, GLint slice, GLfloat red, GLfloat green, GLfloat blue){
	radius=rad;
	stacks=stack;
	slices=slice;
	r=red;
	g=green;
	b=blue;
}


void Sphere::draw() {
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	glColor3f(r, g, b);
	glutWireSphere(radius, slices ,stacks);
	glPopMatrix();
}
