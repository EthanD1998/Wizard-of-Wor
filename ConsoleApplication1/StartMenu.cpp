#include "StartMenu.h"
#include "Game.h"
#include <iostream>


StartMenu::StartMenu()
{
	std::cout << "DisplayState StartMenu Created" << std::endl;
	
	font.loadFromFile("Fonts/Adore64.ttf");
	
	text.setFont(font);
	text.setString("PRESS ENTER TO START");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	text.setPosition(sf::Vector2f(425,400));
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

