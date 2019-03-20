#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class DisplayState
{
public:
	DisplayState();
	~DisplayState();
	
	bool hasFocus = true, exists = true;

	sf::Clock *c = nullptr;
	int sec = 0;
	
	virtual DisplayState* nextState();
	virtual void keyEvent(sf::Keyboard::Key&);
	virtual void updateEvents();
	virtual std::string type();
	virtual void draw(sf::RenderWindow* target);	
};
