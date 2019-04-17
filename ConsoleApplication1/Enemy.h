#pragma once
#include "pch.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <iostream>

/*
	Enemy is the base class for all enemies.  
		When more enemies are implemented, they may be children of this class, or be seperate entities.	
		Enemy is a child of Entity.
*/

class Enemy : public Entity
{
	
public:

	Enemy();
	~Enemy();
	
	//		VARIABLES
	Entity* player;
	
	bool invisible = false;
	bool doesShoot = true;
	int shootChance = 1;
	//		FUNCTIONS
	
	void columnOpacity();
	
	void handleEvents() override;
	/*
		Overriden from Entity.h
			Handles all the enemies events.
			Stuff like collision and shooting (eventually)
	*/
	void newDirection();
	/*
		Part of the automatic movement
			It's funky.
	*/
	virtual std::string type() override;
	/*
		Returns the type of Entity.
	*/
	sf::Vector2f current, prev;
};

