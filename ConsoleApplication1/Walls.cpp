#include "pch.h"
#include "Walls.h"

//please add more comments
//0 = top, 1 = right, 2 = bottom, 3 = left
Walls::Walls()
{
	Wall.setSize(sf::Vector2f(60, 5));
	Wall.setOrigin(sf::Vector2f(Wall.getSize().x / 2, Wall.getSize().x / 2));
	Wall.setFillColor(sf::Color::Blue);
}

Walls::Walls(int side, int x, int y)
{
	Wall.setSize(sf::Vector2f(60, 5));
	Wall.setOrigin(sf::Vector2f(Wall.getSize().x / 2, Wall.getSize().x / 2));
	Wall.setFillColor(sf::Color::Blue);
	Wall.setRotation(side * 90);
	Wall.setPosition(sf::Vector2f(Wall.getSize().x * x + 60, Wall.getSize().x * y + 60));
}

Walls::Walls(int side, int x, int y, sf::Color color)
{
	Wall.setSize(sf::Vector2f(60, 5));
	Wall.setOrigin(sf::Vector2f(Wall.getSize().x / 2, Wall.getSize().x / 2));
	Wall.setFillColor(color);
	Wall.setRotation(side * 90);
	Wall.setPosition(sf::Vector2f(Wall.getSize().x * x + 60, Wall.getSize().x * y + 60));
}

Walls::~Walls()
{

}

void Walls::setWall(int side, int x, int y)
{
	Wall.setRotation(side * 90);
	Wall.setPosition(sf::Vector2f(Wall.getSize().x * x, Wall.getSize().x * y));
	return;
}

sf::RectangleShape Walls::getWall()
{
	return Wall;
}

void Walls::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Wall, states);
}
