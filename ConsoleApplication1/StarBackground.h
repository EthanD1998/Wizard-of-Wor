#pragma once
#include "pch.h"
#include <iostream>
#include "DisplayState.h"
#include <SFML/Graphics.hpp>

class StarBackground : public DisplayState
{
public:
	StarBackground();
	~StarBackground();
	
	std::vector<sf::CircleShape> shapes;
	int frameCount = 0;

	void updateEvents() override;
	std::string type() override;
	void draw(sf::RenderWindow*) override;	
};

