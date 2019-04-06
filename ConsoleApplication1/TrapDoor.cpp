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
	
	font.loadFromFile("Fonts/Adore.ttf");
		
	text.setFont(font);
	text.setString("0");
	text.setCharacterSize(20);
	
	text.setFillColor(sf::Color::Yellow);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(660,420));
		
	std::cout << "Spawned TrapDoor @ (" << door.getPosition().x / 60 << ", " << door.getPosition().y / 60 << ")\n";
	
	for(int i = 0; i < entities->size(); i++)
	{
		if(entities->at(i)->type() == "Player")
		{
			player = entities->at(i);
			break;
		}
	}		
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
	
	if(player->sprite.getPosition().y < door.getPosition().y + 5)
	{
		player->killable = true;
		std::cout << "Closed Doors\n";
		open = false;
		level->getCell(11, 5)->addWall(Walls(2, 11, 5, sf::Color::Blue));
		Alive = false;
		return true;
	}
	else
	{
		int temp;
		//we don't need timeAlive for this Entity, so we use it for a timer
		temp = round(clock.getElapsedTime().asSeconds());
		if(temp > timeAlive)
		{
			timeAlive++;
		}
				switch(timeAlive)
		{
			case 11:
				player->sprite.setPosition(sf::Vector2f(player->sprite.getPosition().x, player->sprite.getPosition().y - 10));
				break;
			default:
				text.setString(std::to_string(timeAlive));
				break;
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

void TrapDoor::draw(sf::RenderWindow* target)
{
	target->draw(text);
}
