#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class DisplayState
{
public:
	DisplayState();
	~DisplayState();
	
	bool hasFocus = true, exists = true;
	
	virtual void keyEvent(sf::Keyboard::Key&);
	virtual void updateEvents();
	virtual std::string type();
	
	DisplayState* nextState();
	
	virtual void draw(sf::RenderTarget* target);	
};

