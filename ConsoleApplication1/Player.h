#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>

class Player : public Entity
{
	
public:

	Player(Map*);
	~Player();
	void handleEvents() override;
	//void draw(sf::RenderWindow*) override;
	
	std::string type() override;
	void keyInput();

};

