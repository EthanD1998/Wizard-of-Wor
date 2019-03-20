#pragma once
#include "pch.h"
#include "DisplayState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

/*
	StartMenu is the menu the game loads into when it starts.
	Shows a simple prompt.
*/

class StartMenu : public DisplayState
{
public:
	StartMenu();
	~StartMenu();
	
	//		VARIABLES
	
	sf::Text text, second;
	/*
		The two text objects we'll use
	*/
	sf::Font font;
	/*
		The font we use
	*/
	bool triggered = false;	
	/*
		If the menu has been triggered
	*/
	
	//		FUNCTIONS
	
	void updateEvents() override;
	/*
		Overridden from DisplayState
		Handles all the events for the state
	*/
	DisplayState* nextState() override;
	/*
		Returns the next state of the state
	*/
	void keyEvent(sf::Keyboard::Key&) override;
	/*
		Key events for the menu
	*/
	std::string type() override;
	/*
		Returns the type of DisplayState
	*/
	void draw(sf::RenderWindow*) override;	
	/*
		draws all the shapes.
	*/
};

