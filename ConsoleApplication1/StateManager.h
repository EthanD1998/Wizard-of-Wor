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
	
	std::vector<DisplayState*> gameStates;
	
	
};

