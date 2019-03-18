#include "DisplayState.h"
#include <iostream>


DisplayState::DisplayState()
{
	std::cout << "DisplayState Created" << std::endl;	
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

void DisplayState::draw(sf::RenderTarget* target)
{	
}

std::string DisplayState::type()
{
	return "DisplayState";
}

