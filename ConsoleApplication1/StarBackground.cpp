#include "pch.h"
#include "StarBackground.h"

StarBackground::StarBackground()
{
	hasFocus = false;
	
	std::cout << "DisplayState StarBackground Created" << std::endl;
	
	for (int i = 0; i < 650; i++)
	{
		sf::CircleShape c(1);
		c.setFillColor(color);
		c.setPosition(sf::Vector2f(rand() % 850, rand() % 600));
		shapes.push_back(c);
	}

}

StarBackground::~StarBackground()
{
}

void StarBackground::draw(sf::RenderWindow* target)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		target->draw(shapes.at(i));
	}

}

void StarBackground::updateEvents()
{
	sf::Color c;
	for (int i = 0; i < shapes.size(); i++)
	{
		shapes.at(i).setFillColor(sf::Color(color.r, color.g, color.b, rand() % 155 + 100));
	}
}

std::string StarBackground::type()
{
	return "StarBackground";
}

