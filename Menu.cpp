#include "menu.h"


menu::menu(float width, float height)
{
	if (!font.loadFromFile("Data/arial.ttf")) {}

	//play
	MainMenu[0].setFont(font);
	MainMenu[0].setFillColor(sf::Color::Blue);
	MainMenu[0].setString("Start Game");
	MainMenu[0].setCharacterSize(50);
	MainMenu[0].setPosition(sf::Vector2f(width / 2 - 120, height / 2 / (max_main_menu + 1)*4));



	//Options
	MainMenu[1].setFont(font);
	MainMenu[1].setFillColor(sf::Color::White);
	MainMenu[1].setString("Controls");
	MainMenu[1].setCharacterSize(50);
	MainMenu[1].setPosition(sf::Vector2f(width / 2 - 100, height / 2 / (max_main_menu + 1) * 5));

	//Exit
	MainMenu[2].setFont(font);
	MainMenu[2].setFillColor(sf::Color::White);
	MainMenu[2].setString("Exit");
	MainMenu[2].setCharacterSize(50);
	MainMenu[2].setPosition(sf::Vector2f(width / 2 - 60, height / 2 / (max_main_menu + 1) * 6));

	MainMenuSelected = 0;

}

menu::~menu()
{
}

//Function of drawing main menu
void menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(MainMenu[i]);
	}
}

void menu::moveup()
{
	if (MainMenuSelected - 1 >= -1) //check if not on the first item (play)
	{
		MainMenu[MainMenuSelected].setFillColor(sf::Color::White); //change the previous item's color
		MainMenuSelected--; // move to the upper item
		if (MainMenuSelected == -1)
			MainMenuSelected = 2;
		MainMenu[MainMenuSelected].setFillColor(sf::Color::Blue); //change the new item's color
	}

}

void menu::movedown()
{
	if (MainMenuSelected + 1 <= max_main_menu) //check if not on the last item (exit)
	{
		MainMenu[MainMenuSelected].setFillColor(sf::Color::White); //change the previous item's color

		MainMenuSelected++; //move to the lower item
		if (MainMenuSelected == 3)
			MainMenuSelected = 0;
		MainMenu[MainMenuSelected].setFillColor(sf::Color::Blue); //change the new item's color
	}
}

