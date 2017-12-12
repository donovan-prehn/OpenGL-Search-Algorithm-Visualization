/*
 * Maze.hpp
 *
 *  Created on: Dec 5, 2017
 *      Author: dny
 */

#ifndef SRC_MAZE_HPP_
#define SRC_MAZE_HPP_
#include "Cube.hpp"
#include <GL/glut.h>
#include <list>
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <queue>

struct tile{
	GLint x;
	GLint y;

	bool operator==(const tile& rhs) const{
		return x == rhs.x && y==rhs.y;
	}
};

class Maze {

 public:
	//Maze variables
	GLint size;
	tile start;
	tile end;

	//Maze containers
	GLint **board;
	GLint **visited;

	//Search algorithm
	queue<tile> tiles;
	bool done;
	tile agent;

	std::list<Cube> cubes;

	Maze();
	Maze(GLint size);
	void click(GLint x, GLint y, GLint width, GLint height);
	GLint get(GLint x, GLint y);
	void BFS();
	void DFS();
	void draw(GLint width, GLint height);
	void draw3D();
	void draw_2Dgrid();
	void draw_3Dgrid();
};


#endif /* SRC_MAZE_HPP_ */
