#pragma once
#include <iostream>
#include <time.h>
#include <vector>

#define N 20
#define M 25

class maze {
private:
	struct parameters {
		bool north = false;
		bool south = false;
		bool west = false;
		bool east = false;
	};
	bool used[N + 2][M + 2] = { 0 };
	int arraySteps[N + 2][M + 2] = { 0 };
	int maxStep = 0;
	int Level = 0;
public:
	parameters mazeParameters[N + 2][M + 2];
	int startX = 1, startY = 1, finishX = 1, finishY = 1;
	int myMaze[N + 2][M + 2] = { 0 };
	void createMaze(int level) {
		Level = level;
		maxStep = 0;
		startX = 1, startY = 1, finishX = 1, finishY = 1;
		initialFilling();
		recCreateMaze(startX, startY);
		arrMaze();
		start();
		clean();
		steps(1, 1, 1);
		finish();
	}
	void recCreateMaze(int x, int y) {
		used[x][y] = true;
		int number_paths = (rand() % 3) + 3;
		bool path[4] = { 0 };
		bool usedPath[4] = { 0 };
		int id = 0;
		while (number_paths) {
			bool r = rand() % 2;
			if (r == true) {
				path[id] = true;
				number_paths--;
			}
			id++;
			id = id % 4;
		}

		int passed = 4;
		while (passed) {
			int i = rand() % 4;
			if (usedPath[i] == false) {
				usedPath[i] = true;
				passed--;
			}
			if (path[i] == true && x != 1 && i == 0 && used[x - 1][y] == false) {
				mazeParameters[x][y].north = true;
				mazeParameters[x - 1][y].south = true;
				if (used[x - 1][y] == false) {
					recCreateMaze(x - 1, y);
				}
			}
			else if (path[i] == true && x != N - 1 && i == 1 && used[x + 1][y] == false) {
				mazeParameters[x][y].south = true;
				mazeParameters[x + 1][y].north = true;
				if (used[x + 1][y] == false) {
					recCreateMaze(x + 1, y);
				}
			}
			else if (path[i] == true && y != 1 && i == 2 && used[x][y - 1] == false) {
				mazeParameters[x][y].west = true;
				mazeParameters[x][y - 1].east = true;
				if (used[x][y - 1] == false) {
					recCreateMaze(x, y - 1);
				}
			}
			else if (path[i] == true && y != M - 1 && i == 3 && used[x][y + 1] == false) {
				mazeParameters[x][y].east = true;
				mazeParameters[x][y + 1].west = true;
				if (used[x][y + 1] == false) {
					recCreateMaze(x, y + 1);
				}
			}
		}
	}
	bool start() {
		for (int i = 1; i < N; i++) {
			for (int j = 1; j < M; j++) {
				if (used[i][j] == true) {
					startX = i;
					startY = j;
					return true;
				}
			}
		}
		return false;
	}
	void steps(int x, int y, int step) {
		arraySteps[x][y] = step;
		if (step > maxStep) maxStep = step;
		used[x][y] = true;
		if (mazeParameters[x][y].north == true && used[x - 1][y] == false) {
			steps(x - 1, y, step + 1);
		}
		if (mazeParameters[x][y].south == true && used[x + 1][y] == false) {
			steps(x + 1, y, step + 1);
		}
		if (mazeParameters[x][y].west == true && used[x][y - 1] == false) {
			steps(x, y - 1, step + 1);
		}
		if (mazeParameters[x][y].east == true && used[x][y + 1] == false) {
			steps(x, y + 1, step + 1);
		}

	}
	bool finish() {
		for (int i = 1; i < N; i++) {
			for (int j = 1; j < M; j++) {
				if (arraySteps[i][j] == maxStep) {
					finishX = i;
					finishY = j;
					return true;
				}
			}
		}
		return false;
	}
	void initialFilling() {
		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				mazeParameters[i][j].north = false;
				mazeParameters[i][j].south = false;
				mazeParameters[i][j].west = false;
				mazeParameters[i][j].east = false;
				myMaze[i][j] = 0;
				arraySteps[i][j] = 0;
				used[i][j] = false;
			}
		}
	}
	void clean() {
		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				used[i][j] = false;
			}
		}
	}
	void arrMaze() {
		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == false && mazeParameters[i][j].west == false && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 0;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == false && mazeParameters[i][j].west == true && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 1;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == false && mazeParameters[i][j].west == false && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 2;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == false && mazeParameters[i][j].west == false && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 3;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == true && mazeParameters[i][j].west == false && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 4;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == false && mazeParameters[i][j].west == true && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 5;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == true && mazeParameters[i][j].west == false && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 6;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == true && mazeParameters[i][j].west == true && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 7;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == false && mazeParameters[i][j].west == true && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 8;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == false && mazeParameters[i][j].west == false && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 9;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == true && mazeParameters[i][j].west == false && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 10;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == true && mazeParameters[i][j].west == false && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 11;
				}
				else if (mazeParameters[i][j].north == false && mazeParameters[i][j].south == true && mazeParameters[i][j].west == true && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 12;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == true && mazeParameters[i][j].west == true && mazeParameters[i][j].east == false) {
					myMaze[i][j] = 13;
				}
				else if (mazeParameters[i][j].north == true && mazeParameters[i][j].south == false && mazeParameters[i][j].west == true && mazeParameters[i][j].east == true) {
					myMaze[i][j] = 14;
				}
				else {
					myMaze[i][j] = 15;
				}
			}
		}
	}
	void print() {
		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				std::cout << used[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};