#include "pch.h"
#include "Cell.h"
#include <iostream>

Cell::Cell()
{
}


Cell::~Cell()
{
}


void Cell::set(bool iWalls[4], int x, int y, sf::Color c)
{
	for (int i = 0; i < 4; i++)
	{
		isWall[i] = iWalls[i];
		if (iWalls[i])
		{
			Wall.push_back(Walls(i, x, y, c));
		}
	/*	std::cout << iWalls[i];
		std::cout << isWall[i];*/
	}
	//std::cout << std::endl;
}

void Cell::color(sf::Color c)
{
	for (int i = 0; i < Wall.size(); i++)
	{
		Wall.at(i).Wall.setFillColor(c);
	}
}

void Cell::image(const sf::Texture t)
{
	for (int i = 0; i < Wall.size(); i++)
	{
		Wall.at(i).Wall.setTexture(&t);
	}
}

std::vector<Walls> Cell::getWalls()
{
	return Wall;
}


bool Cell::hasWall()
{
	bool isWall = false;
	if (Wall.size() > 0)
		isWall = true;
	return isWall;
}

void Cell::addWall(Walls newWall)
{
	Wall.push_back(newWall);
}

void Cell::deleteLastWall()
{
	Wall.pop_back();
}

void Cell::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < Wall.size(); i++)
	{
		target.draw(Wall.at(i), states);
	}
}
