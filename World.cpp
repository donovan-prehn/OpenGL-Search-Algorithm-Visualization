/**
 * File: World.hpp
 */

#include "World.hpp"

#include <stdio.h>
using namespace std;

World::World() {

	//declare the obstructions in the maze
	maze_object = new Sphere(10,20,20,1,0,0);

	int i,j;
	count = 0;
	//set to 0 as default
	for (i = 0; i<10; i++){
		for (j = 0; j<10; j++){
			obstructions[i][j] = 0;
		}
	}
	//make obstructions
	obstructions[0][3] = 1;
	obstructions[1][3] = 1;
	obstructions[2][3] = 1;
	obstructions[3][3] = 1;
	obstructions[4][3] = 1;
	obstructions[5][3] = 1;
	obstructions[6][3] = 1;
	obstructions[9][5] = 1;
	obstructions[2][7] = 1;
	obstructions[6][5] = 1;
	obstructions[1][9] = 1;
	obstructions[6][9] = 1;

	//create cubes
	for (i = 0; i < 10; i++){
		for (j = 0; j<10; j++){
			//if there is a cube at i,j

			if(obstructions[i][j] == 1 ){
				cubes.push_front(Cube());
				cubes.front().scale_change(-0.5);
				cubes.front().translate(0.5,0,0.5);
				cubes.front().translate(i, 0, j);

			}
		}
	}

}

World::~World(){

}
//draws world
void World::draw_world() {

	//maze_object->draw();
	draw_obstructions();
}
//draws all the obstructions
void World::draw_obstructions(){
	for (std::list<Cube>::iterator it = cubes.begin(); it != cubes.end(); ++it){
		it->draw();
	}
}

void World::reset_world(){

}

//draws the floor
void World::draw_floor(){

}

void World::draw_grid(){
	glPushMatrix();

	//draw x axis
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
	glEnd();

	//draw y axis
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,10,0);
	glEnd();

	//draw z axis
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,0,10);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	int i;
	for(i=0;i<=10;i++){
		glBegin(GL_LINES);
			glVertex3f(i,0,0);
			glVertex3f(i,0,10);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0,0,i);
			glVertex3f(10,0,i);
		glEnd();
	}
	glPopMatrix();
}
