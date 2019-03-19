#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

//#include "DisplayState.h"

#include "Game.h"
//#include "Game.cpp"

#include "StartMenu.h"
//#include "StartMenu.cpp"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	void init();
	void kill(int);
	
	std::vector<DisplayState*> gameStates;
	
	
};

