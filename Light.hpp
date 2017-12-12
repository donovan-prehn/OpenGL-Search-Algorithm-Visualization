
#ifndef CLIGHT_H
#define CLIGHT_H

#include <GL/glut.h>
#include "Point.hpp"
#include "Vector.hpp"

class Light {
 public:
	//light and shading
	GLfloat x,y,z;
	GLfloat I;
	GLfloat Rd;
	GLfloat Ia;
	GLfloat Ra;
	bool On;
	GLint Size;

	Light();
	void pointLight(GLfloat x, GLfloat y, GLfloat z, GLfloat amb, GLfloat diff);
	void set(Point Eye, Point look, Vector up);
	void set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz);
	void printLight(void);
	void Increment(GLfloat pointLight, GLfloat ambientLight, GLfloat diffusion, GLfloat ambientReflect);
	void Draw(void);
	void reset_Light();
	void rotate(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
};
#endif


