#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>

/*
	DisplayState is the parent class for all DisplayStates.
		DisplayStates are screens that need drawn.
*/

class DisplayState
{
public:
	DisplayState();
	~DisplayState();
	
	/*
		If the DisplayState hasFocus, the StateManager will pass it keyEvents.
			If multiple DisplayState are being drawn, only one should recieve keyEvents.
			This will be the DisplayState with focus.
			
		If the DisplayState doesn't exist, the StateManager will kill it.
			It will also create the object defined in nextState();
	*/
	
	//		VARIABLES
	
	bool hasFocus = true, exists = true, getsEvents = true, hasNext = true;
	
	int sec = 0;
	sf::Clock clock;
	/*
		The clock and second counter used to time events.
			This is a failproof way to tell when x seconds have passed.
	*/
	
	//		FUNCTIONS
	
	virtual DisplayState* nextState();
	/*
		nextState will return a new DisplayState, as to allow the StateManager to easily create the next DisplayState/
			ex: StartMenu's nextState() returns a new Game() object.
	*/
	virtual void keyEvent(sf::Keyboard::Key&);
	/*
		If a DisplayState needs to recieve keyEvents when in focus, it can override this function.
	*/
	virtual void updateEvents();
	/*
		Called by the StateManager every frame.
			Each DisplayState will override this.
			This allows each DisplayState to handle custom events.
	*/
	virtual void draw(sf::RenderWindow* target);
	/*
		Called by the StateManger every frame.
			Each DisplayState will override this.
			Allows each DisplayState to draw custom shapes.
	*/
	virtual std::string type();
	/*
		Returns the DisplayState's type
	*/
};
