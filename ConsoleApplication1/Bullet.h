#pragma once
#include "pch.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Bullet : public Entity
{

public:

	Bullet(int _facing, Map*);
	~Bullet();
	
	void handleEvents() override;
	/*
		handleEvents() - overridden from Entity.h
			A function called by the game that owns the bullet.
			The function handles Bullet Events, like collision and position.
	*/
	std::string type() override;
	/*
		type() - overridden from Entity.h
			A function that returns the type of the Entity in a std::string.
	*/
};

