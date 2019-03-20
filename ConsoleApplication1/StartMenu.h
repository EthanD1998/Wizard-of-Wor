#pragma once
#include "pch.h"
#include <iostream>
#include "DisplayState.h"
#include <SFML/Graphics.hpp>

class StartMenu : public DisplayState
{
public:
	StartMenu();
	StartMenu(sf::Clock*);
	~StartMenu();
	
	sf::Text text;
	sf::Text second;
	sf::Font font;
	bool triggered = false;
	int frameCount = 0;
	
	void updateEvents() override;
	DisplayState* nextState() override;
	void keyEvent(sf::Keyboard::Key&) override;
	std::string type() override;
	void draw(sf::RenderWindow*) override;	
};

