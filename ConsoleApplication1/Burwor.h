#pragma once
#include "pch.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Burwor : public Enemy
{
public:
	Burwor(Map*, std::vector<Entity*> *);
	~Burwor();

	std::string type() override;
	//void draw(sf::RenderWindow*) override;
};

