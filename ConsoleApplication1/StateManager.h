#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "PauseMenu.h"
#include "StarBackground.h"
#include "StartMenu.h"
#include "FpsCounter.h"

/*
	Class that manages the game's many states.
		Will draw everything and manage the window.
*/

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	void init();
	/*
		Starts the game and doesn't return until the window closes.
	*/
	void kill(int);
	/*
		Kills the DisplayState at the given index
	*/
	bool isPaused();
	/*
		Returns true if the game is paused
	*/
	void pause();
	/*
		Pauses the game
	*/
	std::vector<DisplayState*> gameStates;
	
	
};

