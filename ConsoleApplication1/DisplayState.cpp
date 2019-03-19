#include "DisplayState.h"
#include <iostream>


DisplayState::DisplayState()
{
}

DisplayState::~DisplayState()
{
}

void DisplayState::keyEvent(sf::Keyboard::Key&)
{
}

void DisplayState::updateEvents()
{
}

DisplayState* DisplayState::nextState()
{
	return new DisplayState();
}

void DisplayState::draw(sf::RenderWindow* target)
{
}

std::string DisplayState::type()
{
	return "DisplayState";
}

