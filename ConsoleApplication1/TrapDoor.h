#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "cell.h"
#include "Walls.h"
#include "Map.h"
#include <iostream>

class TrapDoor : public Entity
{
	
public:

	TrapDoor(Map*,std::vector<Entity*>*, int);
	~TrapDoor();
	
	Entity* player;
	int playerType;
	bool open = true;
	sf::RectangleShape door;
	sf::Text text;
	sf::Font font;
	
	void handleEvents() override;
	bool checkCollision() override;

	void draw(sf::RenderWindow*) override;
	std::string type() override;
};

