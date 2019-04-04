#pragma once
#include "pch.h"
#include "DisplayState.h"
#include "StartMenu.h"
#include <SFML/Graphics.hpp>
#include "fstream"
#include <iostream>

/*
	ScoreMenu is the menu the game loads into when it starts.
	Shows a simple prompt.
*/

class ScoreMenu : public DisplayState
{
public:
	
	struct score
	{
		int value;
		std::string name;
	};
	
	ScoreMenu();
	~ScoreMenu();
	
	//		VARIABLES
	
	std::vector<sf::Text> texts;
	/*
		The text objects we'll use
	*/
	sf::Font font;
	/*
		The font we use
	*/
	std::vector<score> scores;
	std::vector<char> newName;
	
	//		FUNCTIONS
	
	void swap(score*, score*);
	void sort();
	
	void keyEvent(sf::Keyboard::Key&) override;
	/*
		Key events for the menu
	*/
	std::string type() override;
	/*
		Returns the type of DisplayState
	*/
	void draw(sf::RenderWindow*) override;	
	/*
		draws all the shapes.
	*/
	void input(sf::Event::TextEvent) override;
	DisplayState* nextState() override;
};

