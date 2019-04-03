#pragma once
#include "pch.h"
#include "DisplayState.h"
#include <iostream>
#include <SFML/Graphics.hpp>

/*
	FpsCounter is the parent class for all DisplayStates.
		DisplayStates are screens that need drawn.
*/

class FpsCounter : public DisplayState
{
public:
	FpsCounter();
	~FpsCounter();
	
	//		VARIABLES
	sf::Font font;
	sf::Text text;
	int frame = 0;
	
	void updateEvents() override;
	virtual void draw(sf::RenderWindow* target);
	virtual std::string type();
};
