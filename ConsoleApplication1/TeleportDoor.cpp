#include "pch.h"
#include "TeleportDoor.h"
#include <iostream>
#include "Entity.h"
#include <cmath>

TeleportDoor::TeleportDoor(map* _map, std::vector<Entity*>* _entities = nullptr)
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
		if(entities->at(i)->type() == "Player" || entities->at(i)->type() == "Enemy")
		{
			if (sprite.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
			{
				entities->at(i)->sprite.setPosition(second.getPosition());
				std::cout << "Closed Doors\n";
				level->getCell(1, 2)->addWall(walls(3, 1, 2, sf::Color::Red));
				level->getCell(11, 2)->addWall(walls(1, 11, 2, sf::Color::Red));
				open = false;
				return true;
			}
			else if (second.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
			{
				entities->at(i)->sprite.setPosition(sprite.getPosition());
				std::cout << "Closed Doors\n";
				level->getCell(1, 2)->addWall(walls(3, 1, 2, sf::Color::Red));
				level->getCell(11, 2)->addWall(walls(1, 11, 2, sf::Color::Red));
				open = false;
				return true;
			}
		}
	}
	return false;
}

void TeleportDoor::checkFrameCount()
{
	frameCount++;
	if((frameCount / 60) / 10 == 1)
	{
		std::cout << "Re-Opened Doors" << std::endl;
		level->getCell(1, 2)->deleteLastWall();
		level->getCell(11, 2)->deleteLastWall();
		open = true;
		frameCount = 0;
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
