#pragma once
#include "pch.h"
#include "DisplayState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	StarBackground is exactly what is sounds like.
	In order to have the stars behind the Game as well, it must be a seperate DisplayState and not just a part of startMenu.	
*/

class StarBackground : public DisplayState
{
public:
	StarBackground();
	~StarBackground();
	
	sf::Color color = sf::Color(0, 187, 103);

	std::vector<sf::CircleShape> shapes;
	/*
		A vector of shapes to draw (stars)
	*/
	void updateEvents() override;
	/*
		Updating the events on each shape
	*/
	std::string type() override;
	/*
		Returns type
	*/
	void draw(sf::RenderWindow*) override;	
	/*
		drawing each shape
	*/
};

