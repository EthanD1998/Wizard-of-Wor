#pragma once
#include "pch.h"
#include "Entity.h"
#include "Map.h"
#include "TrapDoor.h"
#include "SFML/Graphics.hpp"
#include <iostream>

/*
	Player is a child of Entity.
		It is the main player in the game.		
*/

class Player : public Entity
{
	
public:

	Player(Map*, std::vector<Entity*>*, int = 4, int = 0);
	~Player();
	
	//		VARIABLES
	
	std::vector<sf::Sprite> lifeDisplay;
	/*
		Handles the life display
	*/

	sf::Text scoreText;
	sf::Font font;
	
	//		FUNCTIONS
	
	void handleEvents() override;
	/*
		Handles the player events, like movement
	*/
	std::string type() override;
	/*
		returns the type of Entity
	*/
	void draw(sf::RenderWindow*) override;

	void respawn() override;

	void keyInput();
	/*
		Passes single key presses to the player.
	*/

};

