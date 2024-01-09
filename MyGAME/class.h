#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
int score = 0;

using namespace sf;
class CAR {
private:

protected:

	const int borderLeft = 200;
	const int borderRight = 400;
public:
	int car_Width;
	int car_Height;
	int cX = 0, cY = 0;
	double dx, dy; ///скорость
	FloatRect rect; //координаты 
	Sprite sprite; //картинка
	CAR(Texture& image, int carWidth, int carHeight) {
		sprite.setTexture(image);
		dx = dy = 0;
		car_Width = carWidth;
		car_Height = carHeight;
	}
};
class oncomingS;
class Player : public CAR {
private:
	friend bool exident(Player&, oncomingS&);
public:

	Player(Texture& image, int carWidth, int carHeight) :CAR(image, carWidth, carHeight) {
		sprite.setTexture(image);
		cX = 200;
		cY = 500;
		rect = FloatRect(cX, cY, carWidth, carHeight);
		car_Width = carWidth;
		car_Height = carHeight;
	}
	void update(float time) {
		rect.left += dx * time;
		rect.top += dy * time;
		sprite.setPosition(rect.left, rect.top);
		dx = 0;
		dy = 0;
	}
	
};

class oncomingS :public CAR {
private:
	double dys = 0.05;
	friend bool exident(Player&, oncomingS&);
	friend void rand(oncomingS&, oncomingS&);
public:
	oncomingS(Texture& image, int carWidth, int carHeight, int cX, int cY) :CAR(image, carWidth, carHeight) {
		sprite.setTexture(image);
		rect = FloatRect(cX, cY, carWidth, carHeight);
		car_Width = carWidth;
		car_Height = carHeight;
	}
	void update1(float time, double speed) {
		rect.top += speed * time;
		sprite.setPosition(rect.left, rect.top);
	}
};

bool exident(Player& obj, oncomingS& jbjs) {
	if (((obj.rect.left >= (jbjs.rect.left - jbjs.car_Width)) && (obj.rect.left <= (jbjs.rect.left + jbjs.car_Width)))
		&& ((obj.rect.top + jbjs.car_Height >= (jbjs.rect.top)) && (obj.rect.top - jbjs.car_Height) <= (jbjs.rect.top)))
	{return true;}
	else return false;
}

void rand(oncomingS& jbjs1, oncomingS& jbjs2, oncomingS& jbjs3) {
	int coord;
	int a = 100;
	int b = 450;
	srand(time(0));
	bool flag = true;
	while (flag) {
		int res = a + rand() % (b - a + 1);
		if (!((res >= (jbjs1.rect.left - jbjs1.car_Width)) && (res <= (jbjs1.rect.left + jbjs1.car_Width)))
			&& !((res >= (jbjs2.rect.left - jbjs2.car_Width)) && (res <= (jbjs2.rect.left + jbjs2.car_Width)))) {
			coord = res;
			flag = false;
		}
	}
	jbjs3.rect.left = coord;
	jbjs3.rect.top = 0;
	score++;
}
