#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>

class Enemy : public Entity
{
	
public:

	Enemy(Map*, std::vector<Entity*> *);
	~Enemy();
	void handleEvents() override;
	void newDirection();

	int temp;
	std::string type() override;

};

