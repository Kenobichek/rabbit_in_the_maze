#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include "maze.h"

#define N 20
#define M 25

class fox {
private:
	struct parameters {
		bool north = false;
		bool south = false;
		bool west = false;
		bool east = false;
	};
	struct point {
		int x;
		int y;
	};
	bool mySort(const point& a, const point& b) {
		return paths[a.x][a.y] > paths[b.x][b.y];
	}
	//int fox_dx = N - 1, fox_dy = M - 1;
	int paths[N + 2][M + 2] = { 0 };

public:
	int fox_dx = N - 1, fox_dy = M - 1;
	void move(maze Maze) {
		//paths[fox_dx][fox_dy] += 1;
		std::vector <point> vec;
		//visibility(Maze);
		if (Maze.mazeParameters[fox_dx][fox_dy].north == true) {
			if (Maze.myMaze[fox_dx - 1][fox_dy] >= 2) {
				vec.push_back({ fox_dx - 1 ,fox_dy });
			}
		}
		if (Maze.mazeParameters[fox_dx][fox_dy].south == true) {
			if (Maze.myMaze[fox_dx + 1][fox_dy] >= 2) {
				vec.push_back({ fox_dx + 1 ,fox_dy });
			}
		}
		if (Maze.mazeParameters[fox_dx][fox_dy].west == true) {
			if (Maze.myMaze[fox_dx][fox_dy - 1] >= 2) {
				vec.push_back({ fox_dx ,fox_dy - 1});
			}
		}
		if (Maze.mazeParameters[fox_dx][fox_dy].east == true) {
			if (Maze.myMaze[fox_dx][fox_dy + 1] >= 2) {
				vec.push_back({ fox_dx ,fox_dy + 1 });
			}
		}
		for (int i = 1; i < vec.size(); i++) {
			for (int j = i; j > 0 && mySort(vec[j - 1], vec[j]); j--) {
				point tmp = vec[j];
				vec[j] = vec[j - 1];
				vec[j - 1] = tmp;
			}
		}
		for (int i = 0; i < vec.size(); i++) {
			fox_dx = vec[i].x;
			fox_dy = vec[i].y;
			break;
		}
		visibility(Maze);
		//print();
	}
	void visibility(maze Maze) {
		paths[fox_dx][fox_dy] = 1;
		int tmpX = fox_dx, tmpY = fox_dy;
		while (Maze.mazeParameters[tmpX][tmpY].north == true) {
			tmpX--;
			paths[tmpX][tmpY] += 1;
		}
		tmpX = fox_dx, tmpY = fox_dy;
		while (Maze.mazeParameters[tmpX][tmpY].south == true) {
			tmpX++;
			paths[tmpX][tmpY] += 1;
		}
		tmpX = fox_dx, tmpY = fox_dy;
		while (Maze.mazeParameters[tmpX][tmpY].west == true) {
			tmpY--;
			paths[tmpX][tmpY] += 1;
		}
		tmpX = fox_dx, tmpY = fox_dy;
		while (Maze.mazeParameters[tmpX][tmpY].east == true) {
			tmpY++;
			paths[tmpX][tmpY] += 1;
		}
	}
	void print() {
		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				std::cout << paths[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};