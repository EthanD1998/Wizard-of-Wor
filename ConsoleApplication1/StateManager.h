#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "StarBackground.h"
#include "StartMenu.h"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	void init();
	void kill(int);
	
	sf::Clock clock;
	std::vector<DisplayState*> gameStates;
	
	
};

