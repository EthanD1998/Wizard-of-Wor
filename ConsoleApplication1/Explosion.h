#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>

class Explosion : public Entity
{
	
public:

	Explosion(sf::Vector2f);
	~Explosion();
	
	void handleEvents() override;
	void draw(sf::RenderWindow*) override;
	std::string type() override;
};

