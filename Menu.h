#pragma once
#define max_main_menu 3
#include<SFML/Graphics.hpp>
class menu
{
public:
	menu(float width, float height);
	void draw(sf::RenderWindow& windwow);
	void moveup();
	void movedown();

	int MainMenuPressed()
	{
		return MainMenuSelected;
	}

	~menu();

private:
	int MainMenuSelected;
	sf::Font font;
	sf::Text MainMenu[max_main_menu];

};