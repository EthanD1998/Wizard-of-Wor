#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class DisplayState
{
public:
	DisplayState();
	~DisplayState();
	
	bool hasFocus = true, exists = true;
	

	//std::vector<sf::RectangleShape> shapes;
	std::vector<sf::CircleShape> shapes;

	virtual DisplayState* nextState();
	virtual void keyEvent(sf::Keyboard::Key&);
	virtual void updateEvents();
	virtual std::string type();
	virtual void draw(sf::RenderWindow* target);	
};