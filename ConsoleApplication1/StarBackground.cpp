#include "pch.h"
#include "StarBackground.h"

StarBackground::StarBackground()
{
	hasFocus = false;
	color = sf::Color(0, 187, 103);
	std::cout << "DisplayState StarBackground Created" << std::endl;
	
	for (int i = 0; i < 650; i++)
	{
		sf::RectangleShape c(sf::Vector2f(1.5,1.5));
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
	int t = 0;

	for (int i = 0; i < shapes.size(); i++)
	{
		if (i % 100 == 0) t = rand() % 155 + 100;
		shapes.at(i).setFillColor(sf::Color(color.r, color.g, color.b, t));
	}
}
	

std::string StarBackground::type()
{
	return "StarBackground";
}

