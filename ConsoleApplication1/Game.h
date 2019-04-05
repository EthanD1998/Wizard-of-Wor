#pragma once
#include "pch.h"
#include "DisplayState.h"
#include "ScoreMenu.h"
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Burwor.h"
#include "Thorwor.h"
#include "Garwor.h"
#include "TeleportDoor.h"
#include "TrapDoor.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

/*
	Game class is a child of DisplayState.
		It handles almost all aspects of the actual game.
*/

class Game : public DisplayState
{
public:
	Game(int, int, int = 4, int = 0);
	~Game();
	
	//		VARIABLES
	int gameLevel, nextlvl;
	/*
		The current level
	*/
	std::vector<sf::RectangleShape> shapes;
	/*
		A vector of shapes that the game holds so it can draw them easily.
	*/
	std::vector<Entity*> entities;
	/*
		A vector of Entity pointers the game holds.
			During each frame, the game will call Entity.handleEvents() and draw(Entity) for each item in the vector.
	*/
	Player* player = nullptr;
	Player* playerTwo = nullptr;
	/*
		A reference to a player object so we don't have to search the vector every time we need it.
	*/
	Map level;
	
	
	/*
		Map declaration
	*/
	
	//		FUNCTIONS
	
	void updateEvents() override;
	/*
		updateEvents overridden from parent DisplayState.
			In this function the game will call the events for each entity.
	*/
	void draw(sf::RenderWindow*) override;
	/*
		draw overridden from parent DisplayState.
			This is where the game draws all entities and shapes.
	*/
	void keyEvent(sf::Keyboard::Key&) override;
	/*
		The game needs keyEvents to pause (ADD THIS), as well as do other useful things.
	*/
	std::string type() override;
	/*
		Returns the type of DisplayState.
	*/
	DisplayState* nextState() override;

	void kill(int);
	/*
		Kills the entity at the index given.
			Helpful for killing lots of things easily.
	*/
	bool outsideMap(Entity*);
	/*
		Checks if the Entity passed is outside the map bounds. 
			This happens to enemies often because their movement algorithm doesn't work.
	*/
	int findEntity(std::string);
	/*
		Tries to find the Entity with given type.
			Return -1 if not successful.
	*/
	
};

