#pragma once
#include "pch.h"
#include <iostream>
#include "DisplayState.h"
#include <SFML/Graphics.hpp>

class StartMenu : public DisplayState
{
public:
	StartMenu();
	~StartMenu();
	
	sf::Text text;
	sf::Font font;
	
	DisplayState* nextState() override;
	void keyEvent(sf::Keyboard::Key&) override;
	std::string type() override;
	void draw(sf::RenderWindow*) override;	
};

