#pragma once
#include "pch.h"
#include "DisplayState.h"
#include "StartMenu.h"
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "TeleportDoor.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

/*
	Game class is a child of DisplayState.
		It handles almost all aspects of the actual game.
*/

typedef std::vector<std::vector<std::vector<sf::RectangleShape>>> Map;
/*
	Map declaration to make things cleaner.
*/

class Game : public DisplayState
{
public:
	Game();
	~Game();
	
	//		VARIABLES
	std::vector<sf::RectangleShape> shapes;
	/*
		A vector of shapes that the game holds so it can draw them easily.
	*/
	std::vector<Entity*> entities;
	/*
		A vector of Entity pointers the game holds.
			During each frame, the game will call Entity.handleEvents() and draw(Entity) for each item in the vector.
	*/
	Map map;
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
	void drawMap(sf::RenderWindow*);
	/*
		Draws the map to the RenderWindow passed.
			Called in this.draw
	*/
	void populateMap();
	/*
		Populates the map from a csv file.
			Will be updated to allow different levels to be read.
	*/
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
	bool bulletExists();
	/*
		Checking the vector of entities to see if a bullet exists.
			Called when trying to create a new bullet.
	*/
	
};

