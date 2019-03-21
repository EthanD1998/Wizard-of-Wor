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
	sprite.setPosition(sf::Vector2f(1 * 60 + 61, 2 * 60 + 60));
	
	
	second.setTexture(texture);
	second.setScale(sf::Vector2f(charScale, charScale));
	second.setOrigin(sf::Vector2f(30, 30));
	second.setPosition(sf::Vector2f(11 * 60 + 59, 2 * 60 + 60));	
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
				level->getCell(1, 2)->addWall(walls(3, 1, 2));
				level->getCell(11, 2)->addWall(walls(1, 11, 2));
				open = false;
				return true;
			}
			else if (second.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
			{
				entities->at(i)->sprite.setPosition(sprite.getPosition());
				std::cout << "Closed Doors\n";
				level->getCell(1, 2)->addWall(walls(3, 1, 2));
				level->getCell(11, 2)->addWall(walls(1, 11, 2));
				open = false;
				return true;
			}
		}
	}
	return false;
}

void TeleportDoor::updateTexture()
{
	if(open)
	{
		texture.loadFromFile("Sprites/TeleportDoorOpen.png");
		sprite.setTexture(texture);
		second.setTexture(texture);	
	}
	else
	{
		texture.loadFromFile("Sprites/TeleportDoorClosed.png");
		sprite.setTexture(texture);
		second.setTexture(texture);	
	}
}

void TeleportDoor::checkFrameCount()
{
	frameCount++;
	if((frameCount / 60) / 10 == 1)
	{
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
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));
	radarShape.setFillColor(color);
	radarShape.setPosition(sf::Vector2f((pos.x * 26) + 282 - 26, (pos.y * 26) + 410));

	target->draw(sprite);
	target->draw(radarShape);
	target->draw(second);
}
