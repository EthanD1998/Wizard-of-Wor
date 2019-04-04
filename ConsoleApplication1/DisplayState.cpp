#include "pch.h"
#include "DisplayState.h"

/*
	Almost everything here is blank, as you should NEVER use DisplayState by itself.
		Use the children.
*/

DisplayState::DisplayState()
{
}

DisplayState::~DisplayState()
{
}

void DisplayState::input(sf::Event::TextEvent t)
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

