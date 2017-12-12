#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Cube.hpp"
#include "Vector.hpp"
#include "Sphere.hpp"

#include <iostream>
#include <list>
#include <vector>


class World {
public:

	GLint mazestate[10][10];
	GLint agent[2];

	GLint obstructions[10][10]; // 0 no obstruction 1 obstruction
	GLint count;
	GLint floor[4][3];
	Sphere *maze_object;

	std::list<Cube> cubes;
	// std::vector<Shape*>* ObjectVector;

	World();
	~World();
	void draw_floor(); //draws the floor
	void draw_obstructions(); //draws all of the obstructions
	void draw_world(); // draw all objects in the world
	void reset_world();
	void bfs();
	void draw_grid();

};

#endif
