#include "Cube.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Vector.hpp"

extern Camera myCamera;
extern Light myLight;
extern GLint isShading;
extern GLint shadingType;
Cube::Cube()
{  
	//8 vertices, each with x,y,z
    vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
    vertex[1][0] = -1;vertex[1][1] =  1;vertex[1][2] = -1;
    vertex[2][0] =  1;vertex[2][1] = -1;vertex[2][2] = -1;
    vertex[3][0] =  1;vertex[3][1] =  1;vertex[3][2] = -1;
    vertex[4][0] = -1;vertex[4][1] = -1;vertex[4][2] =  1;
    vertex[5][0] = -1;vertex[5][1] =  1;vertex[5][2] =  1;
    vertex[6][0] =  1;vertex[6][1] = -1;vertex[6][2] =  1;
    vertex[7][0] =  1;vertex[7][1] =  1;vertex[7][2] =  1;

    //6 faces, defined by 4 of the above vertices
    face[0][0] = 0;face[0][1] = 1;face[0][2] = 3;face[0][3] = 2;
    face[1][0] = 3;face[1][1] = 7;face[1][2] = 6;face[1][3] = 2;
    face[2][0] = 7;face[2][1] = 5;face[2][2] = 4;face[2][3] = 6;
    face[3][0] = 4;face[3][1] = 5;face[3][2] = 1;face[3][3] = 0;
    face[4][0] = 5;face[4][1] = 7;face[4][2] = 3;face[4][3] = 1;
    face[5][0] = 6;face[5][1] = 4;face[5][2] = 0;face[5][3] = 2;

    // the face color setting
	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0; //red
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0; faceColor[1][2] = 0.0; //green
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0; faceColor[2][2] = 1.0; //blue
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0; faceColor[3][2] = 0.0; //yellow
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0; faceColor[4][2] = 1.0; //purple
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0; faceColor[5][2] = 1.0; //cyan

	// face normal setting
	cube_face_norm_mc[0][0] = 0.0, cube_face_norm_mc[0][1] = 0.0, cube_face_norm_mc[0][2] = -1.0;
	cube_face_norm_mc[1][0] = 1.0, cube_face_norm_mc[1][1] = 0.0, cube_face_norm_mc[1][2] = 0.0;
	cube_face_norm_mc[2][0] = 0.0, cube_face_norm_mc[2][1] = 0.0, cube_face_norm_mc[2][2] = 1.0;
	cube_face_norm_mc[3][0] = -1.0, cube_face_norm_mc[3][1] = 0.0, cube_face_norm_mc[3][2] = 0.0;
	cube_face_norm_mc[4][0] = 0.0, cube_face_norm_mc[4][1] = 1.0, cube_face_norm_mc[4][2] = 0.0;
	cube_face_norm_mc[5][0] = 0.0, cube_face_norm_mc[5][1] = -1.0, cube_face_norm_mc[5][2] = 0.0;
}

bool Cube::isBackface(int faceindex) {

	GLfloat v[4];
    v[0] = cube_face_norm_mc[faceindex][0];
    v[1] = cube_face_norm_mc[faceindex][1];
    v[2] = cube_face_norm_mc[faceindex][2];
    v[3] = 0.0;
    this->MC.multiply_vector(v);

    Vector vec = Vector(v[0],v[1],v[2]);
    vec.normalize();

    GLfloat x = myCamera.ref.x - myCamera.eye.x;
    GLfloat y = myCamera.ref.y - myCamera.eye.y;
    GLfloat z = myCamera.ref.z - myCamera.eye.z;

    // return true if faceface false otherwise
    return((x * vec.x + y * vec.y + z * vec.z )>= 0);
}
/*
 *
 * Use the lighting model that defines the reflected intensity Id as Id = Rd* I *vector(n) . vector(s) + Ra*Iam,
 * where:
 * 	Rd is  diffusion reflection coefficient,
 * 	I is the the point light intensity,
 * 	Vector(n) is the unit surface normal,
 * 	Vector(s) is the unit vector in the direction of the light source,
 * 	Ra is the ambient reflection coefficient,
 * 	Iam is the ambient light intensity.
 */

//I = 1.0;  //point light intensity
//Ia = 1.0; //ambient light intensity
//Rd = 0.5; //diffusion reflection coefficient
//Ra = 0.5; //ambient reflection coefficient
GLfloat Cube::getFaceShade(int faceindex) {
	GLfloat intensity;

	GLfloat IpKd = myLight.Rd*myLight.I;

	GLfloat v[4];
    v[0] = cube_face_norm_mc[faceindex][0];
    v[1] = cube_face_norm_mc[faceindex][1];
    v[2] = cube_face_norm_mc[faceindex][2];
    v[3] = 0.0;
    this->MC.multiply_vector(v);

    Vector vec = Vector(v[0],v[1],v[2]);
    vec.normalize();

    //middle points on face
    GLfloat mx = (vertex[face[faceindex][0]][0] + vertex[face[faceindex][1]][0] + vertex[face[faceindex][2]][0] + vertex[face[faceindex][3]][0])/4;
    GLfloat my = (vertex[face[faceindex][0]][1] + vertex[face[faceindex][1]][1] + vertex[face[faceindex][2]][1] + vertex[face[faceindex][3]][1])/4;
    GLfloat mz = (vertex[face[faceindex][0]][2] + vertex[face[faceindex][1]][2] + vertex[face[faceindex][2]][2] + vertex[face[faceindex][3]][2])/4;

    //camera points
    GLfloat lx = myLight.x;
    GLfloat ly = myLight.y;
    GLfloat lz = myLight.z;

    Vector L = Vector(lx-mx,ly-my,lz-mz);
    L.normalize();


    intensity = vec.x*L.x + vec.y*L.y + vec.z*L.z;
    intensity = intensity * IpKd;
    return(intensity);

}
void Cube::draw_face(int i)
{
    glBegin(GL_POLYGON);
		glVertex3fv(&vertex[face[i][0]][0]);
		glVertex3fv(&vertex[face[i][1]][0]);
		glVertex3fv(&vertex[face[i][2]][0]);
		glVertex3fv(&vertex[face[i][3]][0]);
    glEnd();
}

void Cube::draw()
{
	glPushMatrix();
	this->ctm_multiply(); // update the CTM
	glScalef(s, s, s);

	for (int i = 0; i < 6; i++){
		draw_face(i);
//		if (!isBackface(i)){
//				//Without shading
//				draw_face(i);
//		}
	}
	glPopMatrix();
}
