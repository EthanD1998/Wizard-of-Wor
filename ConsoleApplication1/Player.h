#pragma once
#include "pch.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <iostream>

/*
	Player is a child of Entity.
		It is the main player in the game.		
*/

class Player : public Entity
{
	
public:

	Player(Map*);
	~Player();
	
	//		VARIABLES
	
	//		FUNCTIONS
	
	void handleEvents() override;
	/*
		Handles the player events, like movement
	*/
	std::string type() override;
	/*
		returns the type of Entity
	*/
	void keyInput();
	/*
		Passes single key presses to the player.
	*/

};

