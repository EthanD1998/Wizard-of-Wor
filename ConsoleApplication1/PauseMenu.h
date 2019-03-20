#pragma once
#include "pch.h"
#include "DisplayState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	PauseMenu is exactly what is sounds like.
*/

class PauseMenu : public DisplayState
{
public:
	PauseMenu(DisplayState*);
	~PauseMenu();
	
	sf::Text text;
	sf::Font font;
	sf::RectangleShape rect;
	DisplayState* game;
	
	std::string type() override;
	/*
		Returns type
	*/
	void draw(sf::RenderWindow*) override;	
	/*
		drawing the text and transparent box.
	*/
	void keyEvent(sf::Keyboard::Key&) override;
	/*
		Key events for the menu
	*/
};

