/*
 * Sphere.hpp
 *
 *  Created on: Oct 21, 2017
 *      Author: dny
 */

#ifndef SRC_SPHERE_HPP_
#define SRC_SPHERE_HPP_

#include "Shape.hpp"

class Sphere: public Shape {
protected:
	GLfloat radius;
	GLfloat r,g,b;
	GLint slices, stacks;

public:
// constructor
	Sphere();
	Sphere(GLfloat radius, GLint stacks, GLint slices, GLfloat r, GLfloat g, GLfloat b);
	// draw all objects in the world
	void draw();


};

#endif /* SRC_HOUSE_HPP_ */
