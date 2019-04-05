#include "pch.h"
#include "TeleportDoor.h"
#include <iostream>
#include "Entity.h"
#include <cmath>

TeleportDoor::TeleportDoor(Map* _map, std::vector<Entity*>* _entities = nullptr)
{
	charScale = 1;
	charMove = 1;
	
	entities = _entities;
	
	level = _map;
	
	texture.loadFromFile("Sprites/TeleportDoorOpen.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sf::Vector2f(30, 30));
	sprite.setPosition(sf::Vector2f(1 * 60 + 60, 2 * 60 + 60));
	
	
	second.setTexture(texture);
	second.setScale(sf::Vector2f(charScale, charScale));
	second.setOrigin(sf::Vector2f(30, 30));
	second.setPosition(sf::Vector2f(11 * 60 + 60, 2 * 60 + 60));	
	second.setRotation(180);
	

	std::cout << "Spawned TeleportDoor @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";
}

TeleportDoor::~TeleportDoor()
{
}

std::string TeleportDoor::type()
{
	return "Teleport Door";
}

bool TeleportDoor::checkCollision()
{
	for(int i = 0; i < entities->size(); i++)
	{
		if (entities->at(i)->type() == "Player" || entities->at(i)->type().find("Enemy") != std::string::npos || entities->at(i)->type().find("Bullet") != std::string::npos)
		{
			if (sprite.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
			{
				entities->at(i)->sprite.setPosition(second.getPosition());
				std::cout << "Closed Doors\n";
				level->getCell(1, 2)->addWall(Walls(3, 1, 2, sf::Color::Red));
				level->getCell(11, 2)->addWall(Walls(1, 11, 2, sf::Color::Red));
				open = false;
				clock.restart();
				return true;
			}
			else if (second.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
			{
				entities->at(i)->sprite.setPosition(sprite.getPosition());
				std::cout << "Closed Doors\n";
				level->getCell(1, 2)->addWall(Walls(3, 1, 2, sf::Color::Red));
				level->getCell(11, 2)->addWall(Walls(1, 11, 2, sf::Color::Red));
				open = false;
				clock.restart();
				return true;
			}
		}
	}
	return false;
}

void TeleportDoor::checkFrameCount()
{
	int temp;
	temp = round(clock.getElapsedTime().asSeconds());
	//I'm using facing here because this Entity doesn't need it and it's an int that's already declared.
	if(temp > facing)
	{
		facing = temp;
	}
	
	switch(facing) //seconds
	{
		case 10:
			std::cout << "Re-Opened Doors" << std::endl;
			level->getCell(1, 2)->deleteLastWall();
			level->getCell(11, 2)->deleteLastWall();
			open = true;
			facing = 0;
			break;
		default:
			break;
	}
}
	
void TeleportDoor::handleEvents()
{
	if(!open)
	{
		checkFrameCount();
	}
	else
	{
		checkCollision();
	}
}

void TeleportDoor::draw(sf::RenderWindow* target)
{	
	if(open)
	{
		target->draw(sprite);
		target->draw(second);
	}
}
