#include "pch.h"
#include "walls.h"

//0 = top, 1 = right, 2 = bottom, 3 = left
walls::walls()
{
	wall.setSize(sf::Vector2f(60, 5));
	wall.setOrigin(sf::Vector2f(wall.getSize().x / 2, wall.getSize().x / 2));
	wall.setFillColor(sf::Color::Blue);

}

walls::walls(int side, int x, int y)
{
	wall.setSize(sf::Vector2f(60, 5));
	wall.setOrigin(sf::Vector2f(wall.getSize().x / 2, wall.getSize().x / 2));
	wall.setFillColor(sf::Color::Blue);
	wall.setRotation(side * 90);
	wall.setPosition(sf::Vector2f(wall.getSize().x * x + 60, wall.getSize().x * y + 60));
}

walls::walls(int side, int x, int y, sf::Color color)
{
	wall.setSize(sf::Vector2f(60, 5));
	wall.setOrigin(sf::Vector2f(wall.getSize().x / 2, wall.getSize().x / 2));
	wall.setFillColor(color);
	wall.setRotation(side * 90);
	wall.setPosition(sf::Vector2f(wall.getSize().x * x + 60, wall.getSize().x * y + 60));
}

walls::~walls()
{

}

void walls::setWall(int side, int x, int y)
{
	wall.setRotation(side * 90);
	wall.setPosition(sf::Vector2f(wall.getSize().x * x, wall.getSize().x * y));
	return;
}

sf::RectangleShape walls::getWall()
{
	return wall;
}

void walls::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(wall, states);
}
