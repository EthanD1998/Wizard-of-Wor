#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "DisplayState.h"
//#include "DisplayState.cpp"

#include "Game.h"
#include "Game.cpp"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	void init();
	void kill(int);
	
	std::vector<DisplayState*> gameStates;
	
	
};

