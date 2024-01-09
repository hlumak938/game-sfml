#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, aboutTexture, menuBackground, bingus;
	menuTexture1.loadFromFile("img/play_button.png");
	menuTexture2.loadFromFile("img/exit_button.png");
	menuBackground.loadFromFile("img/bg_menu.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(230, 420);
	menu2.setPosition(235, 490);
	menuBg.setPosition(0, 0);
	
	while (isMenu == 1)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		Color coloor(119, 34, 2);
		if (IntRect(230, 420, 150, 50).contains(Mouse::getPosition(window))) { menu1.setColor(coloor); menuNum = 1; }
		if (IntRect(235, 490, 150, 50).contains(Mouse::getPosition(window))) { menu2.setColor(coloor); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
}