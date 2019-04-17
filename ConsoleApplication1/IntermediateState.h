#pragma once
#include "DisplayState.h"
#include "Game.h"
class IntermediateState : public DisplayState
{
public:
	IntermediateState(int, int, int, std::vector<int>, bool);
	~IntermediateState();

	int gameIndex, nextGameLevel, gamePCount;
	bool scoreDouble;
	std::vector<int> gamePlayerProp;

	sf::Text text, second;

	sf::Font font;

	void updateEvents() override;

	void keyEvent(sf::Keyboard::Key&) override;

	DisplayState* nextState() override;

	void draw(sf::RenderWindow*) override;
};

