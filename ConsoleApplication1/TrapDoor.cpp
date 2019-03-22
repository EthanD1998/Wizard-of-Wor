#include "pch.h"
#include "TrapDoor.h"
#include "Entity.h"
#include <iostream>
#include <cmath>

TrapDoor::TrapDoor(Map* _map, std::vector<Entity*>* _entities = nullptr)
{
	charScale = 1;
	charMove = 1;
	
	entities = _entities;
	
	door.setSize(sf::Vector2f(60,5));
	door.setFillColor(sf::Color::Green);
	door.setOrigin(door.getLocalBounds().height / 2, door.getLocalBounds().width / 2);
	door.setPosition(sf::Vector2f(747, 360));
	door.setRotation(180);
	
	level = _map;
	
	std::cout << "Spawned TrapDoor @ (" << door.getPosition().x / 60 << ", " << door.getPosition().y / 60 << ")\n";
}

TrapDoor::~TrapDoor()
{
}

std::string TrapDoor::type()
{
	return "Teleport Door";
}

bool TrapDoor::checkCollision()
{
	for(int i = 0; i < entities->size(); i++)
	{
		if(entities->at(i)->type() == "Player")
		{
			if(entities->at(i)->sprite.getPosition().y < door.getPosition().y)
			{
				entities->at(i)->killable = true;
				std::cout << "Closed Doors\n";
				open = false;
				level->getCell(11, 5)->addWall(Walls(2, 11, 5, sf::Color::Red));
				Alive = false;
				return true;
			}
		}
	}
	return false;
}
	
void TrapDoor::handleEvents()
{
	if(open)
	{
		checkCollision();
	}
}
