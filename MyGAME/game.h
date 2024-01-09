#pragma once
#include <SFML/Graphics.hpp>
#include<ctime>
#include<cstdlib>
#include <string>
#include<iostream>
#include "Menu.h"
#include "class.h"
using namespace sf;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGH 700

double speed = 0.05;
std::string stringscore("");

void gameOver(RenderWindow& window);
bool start() {
	score = 0;
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "CAR RACING");
	menu(window);
	Texture car, background, police, cabriolet, lorry;
	car.loadFromFile("img/car_player.png");
	police.loadFromFile("img/c_police.png");
	cabriolet.loadFromFile("img/cabr.png");
	lorry.loadFromFile("img/Lorry_.png");
	background.loadFromFile("img/bg_.jpg");

	Font myfont;
	myfont.loadFromFile("font.ttf");
	Sprite Background(background), Background1(background);
	Player player(car, 65, 120);
	oncomingS c1(police, 65, 120, 100, -300);
	oncomingS c2(cabriolet, 60, 135, 220, -200);
	oncomingS c3(lorry, 65, 156, 400, 0);
	double BackgroundY1 = 0;
	double BackgroundY2 = -1200;
	Clock clock;

	while (window.isOpen())
	{
		stringscore = "SCORE:" + std::to_string(score);
		Text text(stringscore, myfont, 30);
		text.setFillColor(Color::Red);
		text.setPosition(5, 0);
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Background.setPosition(0, BackgroundY1);
		Background1.setPosition(0, BackgroundY2);
		if (BackgroundY2 > 0)
		{
			BackgroundY1 = 0;
			BackgroundY2 = BackgroundY1 - 600;
		}
		BackgroundY1 += (speed + 0.05) * time;
		BackgroundY2 += (speed + 0.05) * time;
		if (score >= 0 && score < 5) { speed = 0.05; }
		if (score > 5 && score < 15) { speed = 0.1; }
		if (score > 15 && score < 100) { speed = 0.2; }
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.dy = - speed;
		}
		else if (player.rect.top > -120 && player.rect.top < SCREEN_HEIGH - 120) { player.dy = 0.05; }
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.dy = speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (player.rect.left < SCREEN_WIDTH - 120)
				player.dx = speed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (player.rect.left > 50)
				player.dx = -speed;
		}
		if (exident(player, c1) == false) {
			if (c1.rect.top < SCREEN_HEIGH + 300) { c1.update1(time, speed + 0.1); }
			else { rand(c2, c3, c1); }
		}
		else { gameOver(window); }

		if (exident(player, c2) == false) {
			if (c2.rect.top < SCREEN_HEIGH + 200) { c2.update1(time, speed - 0.02); }
			else { rand(c1, c3, c2); }
		}
		else { gameOver(window); }

		if (exident(player, c3) == false) {
			if (c3.rect.top < SCREEN_HEIGH + 100) { c3.update1(time, speed - 0.01); }
			else { rand(c2, c1, c3); }
		}
		else { gameOver(window); }


		if (Keyboard::isKeyPressed(Keyboard::Enter)) {return true;}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {return false;}

		player.update(time);
		window.clear();
		window.draw(Background);
		window.draw(Background1);
		window.draw(player.sprite);
		window.draw(c1.sprite);
		window.draw(c2.sprite);
		window.draw(c3.sprite);
		window.draw(text);	
		window.display();
	}
}

void run_game() {
	if (start() == true) {
		run_game();
	}
}

void gameOver(RenderWindow& window) {
	Texture gameover;
	bool isGameOver = 1;
	gameover.loadFromFile("img/gameOver.jpg");
	std::string text_info = "Press Enter to restart game";
	Sprite Gameover(gameover);
	while (isGameOver ==1)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				isGameOver = 0;
		}
		Font myfont;
		myfont.loadFromFile("font.ttf");

		stringscore = "YOUR SCORE:" + std::to_string(score);
		
		Text text(stringscore, myfont, 30);
		Text text1(text_info, myfont, 15);
		text.setPosition(160, 600);
		text1.setPosition(160, 650);
		Color color(201, 91, 8);
		text.setFillColor(color);
		text1.setFillColor(Color::Red);
		window.clear();
		window.draw(Gameover);
		window.draw(text);
		window.draw(text1);
		window.display();
	}
	
}