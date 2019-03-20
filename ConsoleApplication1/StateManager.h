#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "PauseMenu.h"
#include "StarBackground.h"
#include "StartMenu.h"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	void init();
	void kill(int);
	bool isPaused();
	
	std::vector<DisplayState*> gameStates;
	
	
};

