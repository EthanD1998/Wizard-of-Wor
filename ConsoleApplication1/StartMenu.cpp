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
	

	for (int i = 0; i < 650; i++)
	{
		//sf::RectangleShape c(sf::Vector2f(1,1));
		sf::CircleShape c(1);
		c.setFillColor(sf::Color(0, 187, 103));
		c.setPosition(sf::Vector2f(rand() % 850, rand() % 600));
		shapes.push_back(c);
	}

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
	for (int i = 0; i < shapes.size(); i++)
	{
		target->draw(shapes.at(i));
	}

	target->draw(text);
}

void StartMenu::updateEvents()
{
	frameCount++;

	if (frameCount % 4 == 0)
	{
		sf::Color c;
		for (int i = 0; i < shapes.size(); i++)
		{
			c = shapes.at(i).getFillColor();
			shapes.at(i).setFillColor(sf::Color(c.r, c.g, c.b, rand() % 255));
		}
	}
}
	

std::string StartMenu::type()
{
	return "StartMenu";
}

