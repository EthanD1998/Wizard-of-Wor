#include "StartMenu.h"
#include <iostream>


StartMenu::StartMenu()
{
	std::cout << "DisplayState StartMenu Created" << std::endl;
	
	font.loadFromFile("Fonts/Adore64.ttf");
	
	text.setFont(font);
	text.setString("PRESS ENTER TO START");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(200,400));
	
}

StartMenu::~StartMenu()
{
}

DisplayState* StartMenu::nextState()
{
	return new Game();
}

void StartMenu::keyEvent(sf::Keyboard::Key& k)
{
	switch(k)
	{
		case sf::Keyboard::Enter:
				hasFocus = false;
				exists = false;
			break;
		default:
			break;
	}
}

void StartMenu::draw(sf::RenderWindow* target)
{
	target->draw(text);
}

std::string StartMenu::type()
{
	return "StartMenu";
}

