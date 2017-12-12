/*
 * Maze.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: dny
 */
#include "Cube.hpp"
#include "Maze.hpp"
#include <stdio.h>
using namespace std;

Maze::Maze(GLint size){
	this->size=size;

	start.x=0;
	start.y=0;

	end.x=9;
	end.y=9;

	done=false;

	this->board = new GLint*[size];
	for(int i = 0; i < size; ++i)
		board[i] = new GLint[size];


	this->visited = new int*[size];
	for(int i = 0; i < size; ++i)
		visited[i] = new int[size];

	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			board[i][j]=0;
			visited[i][j]=0;
		}
	}
	visited[0][0]=1;
}

Maze::Maze(){
	size=10;

	start.x=0;
	start.y=0;

	end.x=9;
	end.y=9;

	done=false;

	this->board = new GLint*[size];
	for(int i = 0; i < size; ++i)
		board[i] = new GLint[size];

	this->visited = new GLint*[size];
	for(int i = 0; i < size; ++i)
		visited[i] = new GLint[size];

	//could probably be removed
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			board[i][j]=0;
			visited[i][j]=0;
		}
	}
	visited[0][0]=1;
}

void Maze::BFS(){

	if(!tiles.empty() && !done){

		//get value from queue
		tile current;
		current = tiles.front();

		//remove from queue
		tiles.pop();

		//debug
		//printf("%d,%d",current.x,current.y);

		if (current==end){
			done=true;
		}else{
			//visited
			board[current.x][current.y]=2;

			tile up;
			tile down;
			tile right;
			tile left;

			up = current;
			down = current;
			left = current;
			right = current;

			up.y++;
			down.y--;
			left.x--;
			right.x++;


			if(up.y<size && board[up.x][up.y]==0 && visited[up.x][up.y]==0){
				tiles.push(up);
				visited[up.x][up.y]=1;
			}


			if(down.y>=0 && board[down.x][down.y]==0 && visited[down.x][down.y]==0){
				tiles.push(down);
				visited[down.x][down.y]=1;
			}
			if(left.x>=0 && board[left.x][left.y]==0 && visited[left.x][left.y]==0){
				tiles.push(left);
				visited[left.x][left.y]=1;
			}
			if(right.x<size && board[right.x][right.y]==0 && visited[right.x][right.y]==0){
				tiles.push(right);
				visited[right.x][right.y]=1;
			}
		}
	}


}

void Maze::click(GLint x, GLint y, GLint width, GLint height){

	GLint xx = x/(width/size);
	GLint yy = y/(height/size);
	printf("%d,%d\n",xx,yy);
	if(get(xx,yy)){
		board[xx][yy]=0;
	}else{
		board[xx][yy]=1;
	}

}
void Maze::draw(GLint width, GLint height){
	int i,j;
	GLint x_size = width/size;
	GLint y_size = height/size;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){

			//draw obstacle
			if(board[i][size-1-j]==1){
				glColor3f(1.0f,1.0f,1.0f);
				glRectd(i*x_size+5,j*y_size+5,i*x_size+x_size-5,j*y_size+y_size-5);
			}
			// draw searched
			if(board[i][size-1-j]==2){
				glColor3f(0.0f,1.0f,0.0f);
				glRectd(i*80+5,j*80+5,i*80+80-5,j*80+80-5);
			}
			//Draw start
			if(start.x==i && start.y==size-1-j){
				glColor3f(1.0f,0.0f,0.0f);
				glRectd(i*80+5,j*80+5,i*80+80-5,j*80+80-5);
			}
			//Draw ending
			if(end.x==i && end.y==size-1-j){
				glColor3f(1.0f,1.0f,0.0f);
				glRectd(i*80+5,j*80+5,i*80+80-5,j*80+80-5);
			}

		}
	}
}

void Maze::draw3D(){

	int i,j;
	Cube c;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){

			//draw obstacle
			if(board[i][size-1-j]==1){
				glColor3f(1.0f,1.0f,1.0f);
				//glRectd(i*80,j*80,i*80+80,j*80+80);
				c = Cube();
				c.scale_change(-0.5);
				c.translate(0.5,0,0.5);
				c.translate(i, 0, j);
				c.draw();
			}
			//draw searched
			if(board[i][size-1-j]==2){
				glColor3f(0.0f,1.0f,0.0f);
				//glRectd(i*80,j*80,i*80+80,j*80+80);
				c = Cube();
				c.scale_change(-0.5);
				c.translate(0.5,0.0,0.5);
				c.translate(i, 0, j);
				c.draw();
			}
			//draw start
			if(start.x==i && start.y==size-1-j){
				glColor3f(0.0f,1.0f,0.0f);
				//glRectd(i*80,j*80,i*80+80,j*80+80);
				c = Cube();
				c.scale_change(-0.5);
				c.translate(0.5,0.0,0.5);
				c.translate(i, 0, j);
				c.draw();
			}
			//draw end
			if(end.x==i && end.y==size-1-j){
				glColor3f(1.0f,1.0f,0.0f);
				glRectd(i*80,j*80,i*80+80,j*80+80);
				c = Cube();
				c.scale_change(-0.5);
				c.translate(0.5,0,0.5);
				c.translate(i, 0, j);
				c.draw();
			}
		}
	}

}

GLint Maze::get(GLint x, GLint y){
	return board[x][y];
}

void Maze::DFS(){

}

void Maze::draw_3Dgrid(){


//	//draw x axis
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glBegin(GL_LINES);
//		glVertex3f(0,0,0);
//		glVertex3f(10,0,0);
//	glEnd();
//
//	//draw y axis
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glBegin(GL_LINES);
//		glVertex3f(0,0,0);
//		glVertex3f(0,10,0);
//	glEnd();
//
//	//draw z axis
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glBegin(GL_LINES);
//		glVertex3f(0,0,0);
//		glVertex3f(0,0,10);
//	glEnd();
	//draw gridlines
	glPushMatrix();
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
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
		glVertex3f(100,0,100);
		glVertex3f(0,0,100);
	glEnd();
	glPopMatrix();
}
