#pragma once
#include "pch.h"
#include "Map.h"
#include "Cell.h"
#include "Walls.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>


/*
	Entity is the parent class for all types of Entities.
		Entities are sprites with events.

		Entity is a child of sf::Drawable as to make drawing it easier.
			targer.draw(Entity) is how it should be drawn.
*/


class Entity
{
public:
	Entity();
	~Entity();
	
	//		VARIABLES
	
	int team;
	
	Map* level;
	/*
		The pointer to a map
	*/
	int lives = 1;
	/*
		The amount of lives the Entity has.  
			Managed by game.
	*/
	int value = 0;
	/*
		The value to add score to the player
			Is zero for all non-enemy objects
	*/
	sf::Vector2f startPos;
	/*
		The starting position of the Entity.
			Used for respawning only.
	*/
	sf::Vector2f velocity;
	/*
		Velocity that holds an X and Y.
			Each entity should move their own velocity in handleEvents();
	*/
	sf::Texture texture;
	/*
		The texture that the sprite will use.
			Has to be declared here, otherwise it loses focus.
	*/
	sf::Sprite sprite;
	/*
		The sprite used for drawing the Entity
	*/
	sf::RectangleShape radarShape;
	/*
		The shape to be drawn on the radar
	*/
	std::vector<Entity*>* entities;
	/*
		A reference to the Game's list of entities.
			Each Entity needs this to be able to properly handle it's events.
	*/
	sf::Color color = sf::Color::Transparent;
	/*
		The deafult color for the Entities' radar.
			May be removed once the radar functionality is made more effecient.
	*/
	enum directions { N, S, E, W };
	/*
		Directions so each Entity can easily tell which way it's facing.
	*/
	int charScale, charMove;
	/*
		Each Entity has these ints in order to make the scale and movement easier to change.
	*/
	bool Alive = true, killable = true;
	/*
		If the Entity is not Alive, the Game will kill it and de-reference it.
	*/
	int facing = 0;
	/*
		An int that holds the direction the Entity is facing.
	*/
	sf::Clock clock;
	/*
		A clock used to time events
	*/
	int timeAlive = 0;
	
	//		FUNCTIONS
	bool bulletExists();
	/*
		Exactly what it sounds like
	*/
	virtual void shoot();
	/*
		Creates a bullet at the entity's position
	*/
	virtual void respawn();
	/*
		Used to respawn the Entity.
	*/
	virtual bool checkCollision();
	/*
		Most entities need this. 
			If the Entity collides with objects other than the map, it will override this.
	*/
	virtual void handleEvents();
	/*
		Each Entity needs to be able to handle its own events.
			Override this.
	*/
	virtual std::string type();
	/*
		A simple std::string that contains the type of Entity.
	*/
	virtual void draw(sf::RenderWindow* target);
};

