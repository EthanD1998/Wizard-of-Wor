#include "pch.h"
#include "Cell.h"
#include <iostream>

Cell::Cell()
{
}


Cell::~Cell()
{
}


void Cell::set(bool iWalls[4], int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		isWall[i] = iWalls[i];
		if (iWalls[i])
		{
			wall.push_back(walls(i, x, y));
		}
	/*	std::cout << iWalls[i];
		std::cout << isWall[i];*/
	}
	//std::cout << std::endl;
}


std::vector<walls> Cell::getWalls()
{
	return wall;
}


bool Cell::hasWall()
{
	bool isWall = false;
	if (wall.size() > 0)
		isWall = true;
	return isWall;
}

void Cell::addWall(walls newWall)
{
	wall.push_back(newWall);
}

void Cell::deleteLastWall()
{
	wall.pop_back();
}

void Cell::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < wall.size(); i++)
	{
		target.draw(wall.at(i), states);
	}
}
