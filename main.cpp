#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include "maze.h"
#include "foxAI.h"

#define N 20
#define M 25

using namespace sf;

int main() {

	srand(time(NULL));
	maze arr;
	arr.createMaze(0);
	//arr.arrMaze();
	//arr.print();
	//field1.fillTheField();

	RenderWindow app(VideoMode(1000, 800), "Maze");
	app.setFramerateLimit(60);
	//system("dir");

	int w = 35;
	int rabbit_dx = arr.startX,rabbit_dy = arr.startY;
	//int carrot_dx = arr.finishX, carrot_dy = arr.finishY;
	int carrot_dx = 2, carrot_dy = 2;
	//int fox_dx = N - 1, fox_dy = M - 1;
	bool hide_rabbitR = true, hide_rabbitL = false, hide_fox = false;

	fox myFox;
	//float timer = 0, delay = 0.3;
	//Clock clock;

	Font JOKERMAN;
	Font CENTAUR;

	if (!CENTAUR.loadFromFile("CENTAUR.ttf")) {
		std::cout << "can't load font\n";
	}

	int level = 0;
	std::string s = std::to_string(level);

	Texture t;
	t.loadFromFile("images/model.jpg");
	Sprite a(t);

	Texture rl;
	rl.loadFromFile("images/rabbitLeft.png");
	Sprite rabbitLeft(rl);

	Texture rr;
	rr.loadFromFile("images/rabbitRight.png");
	Sprite rabbitRight(rr);
	
	Texture f;
	f.loadFromFile("images/fox.png");
	Sprite fox(f);
	
	Texture c;
	c.loadFromFile("images/carrot.png");
	Sprite carrot(c);

	Clock clock;
	float timer = 0, delay = 5;

	//Сlock timer;
	while (app.isOpen()) {
		/*float time = clock.restart().asSeconds();*/
		//std::cout << timer << " " << delay << "\n";
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Text text("level: " + s, CENTAUR);
		text.setCharacterSize(30);
		text.setPosition(35, 0);
		text.setFillColor(Color::Black);

		Event event;

		while (app.pollEvent(event)) {
			if (event.type == Event::Closed) {
				app.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::R) {
					std::cout << "rabbit: " << rabbit_dx << " " << rabbit_dy << " carrot: " << carrot_dx << " " << carrot_dy << "\n";
				}
				else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
					if (arr.mazeParameters[rabbit_dx][rabbit_dy].east == true) {
						rabbit_dy += 1;
						hide_rabbitL = false;
						hide_rabbitR = true;
					}
				}
				else if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
					if (arr.mazeParameters[rabbit_dx][rabbit_dy].west == true) {
						rabbit_dy -= 1;
						hide_rabbitL = true;
						hide_rabbitR = false;
					}
				}
				else if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
					if (arr.mazeParameters[rabbit_dx][rabbit_dy].north == true) {
						rabbit_dx -= 1;
					}
				}
				else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
					if (arr.mazeParameters[rabbit_dx][rabbit_dy].south == true) {
						rabbit_dx += 1;
					}
				}
			}
		}
		app.clear(Color(14, 125, 136));

		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < M + 1; j++) {
				a.setTextureRect(IntRect(arr.myMaze[i][j] * w, 0, w, w));
				a.setPosition(j * w + 35, i * w + 35);
				app.draw(a);
			}
		}

		if (rabbit_dx == carrot_dx && rabbit_dy == carrot_dy) {
			if (carrot_dx == 1 && carrot_dy == 1) {
				arr.createMaze(level);
			}
			else {
				level++;
				s = std::to_string(level);
				arr.createMaze(level);

				rabbit_dx = arr.startX, rabbit_dy = arr.startY;
				carrot_dx = arr.finishX, carrot_dy = arr.finishY;
				hide_rabbitR = true, hide_rabbitL = false, hide_fox = true;
				myFox.fox_dx = N - 1;
				myFox.fox_dy = M - 1;
			}
		}

		if (rabbit_dx == myFox.fox_dx && rabbit_dy == myFox.fox_dy) {
			
		}

		carrot.setPosition(carrot_dy * w + 35 , carrot_dx * w + 35);
		app.draw(carrot);

		rabbitRight.setPosition(rabbit_dy * w + 35, rabbit_dx * w + 35);
		rabbitLeft.setPosition(rabbit_dy * w + 35, rabbit_dx * w + 35);
		fox.setPosition(myFox.fox_dy * w + 35, myFox.fox_dx * w + 35);

		if (hide_rabbitL) {
			app.draw(rabbitLeft);
		}
		if (hide_rabbitR) {
			app.draw(rabbitRight);
		}
		
		if (hide_fox) {
			if (timer >= delay) {
				std::cout << "\n";
				myFox.move(arr);
				timer = 0;
			}
			app.draw(fox);
		}
		app.draw(text);
		app.display();
	}

	return 0;
}