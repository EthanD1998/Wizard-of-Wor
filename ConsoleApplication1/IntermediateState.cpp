#include "pch.h"
#include "IntermediateState.h"


IntermediateState::IntermediateState(int index, int nextLevel, int pCount, std::vector<int> playerProp, bool doubleDungeon)
{
	gameIndex = index;
	nextGameLevel = nextLevel;
	gamePCount = pCount;
	gamePlayerProp = playerProp;
	scoreDouble = doubleDungeon;

	font.loadFromFile("Fonts/AlienEncounters.ttf");

	second.setFont(font);
	text.setFont(font);

	if (!doubleDungeon)
	{
		text.setString("GET READY");
		text.setFillColor(sf::Color::Yellow);
		second.setString("GO");
		second.setFillColor(sf::Color::Yellow);
	}
	else
	{
		text.setString("Double Score");
		text.setFillColor(sf::Color::Blue);
		second.setString("Dungeon");
		second.setFillColor(sf::Color::Red);
	}
	text.setCharacterSize(100);
	second.setCharacterSize(100);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(420, 200));
	textRect = second.getLocalBounds();
	second.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	second.setPosition(sf::Vector2f(425, 300));


	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color(255, 0, 152));
	colors.push_back(sf::Color(0, 242, 255));
}


IntermediateState::~IntermediateState()
{

}


void IntermediateState::updateEvents()
{
		if (scoreDouble && rand() % 3 == 1)
		{
			text.setFillColor(colors.at(rand() % colors.size()));
			second.setFillColor(colors.at(rand() % colors.size()));
		}
}


DisplayState* IntermediateState::nextState()
{
	return new Game(gameIndex, nextGameLevel, gamePCount, gamePlayerProp, scoreDouble);
}


void IntermediateState::draw(sf::RenderWindow *target)
{
	int temp = round(clock.getElapsedTime().asSeconds());
	if (temp > sec)
	{
		sec = temp;
	}
	target->draw(text);
	if (sec > 1 || scoreDouble)
		target->draw(second);
	if (sec > 2)
	{
		hasFocus = false;
		exists = false;
	}
}

void IntermediateState::keyEvent(sf::Keyboard::Key& k)
{
	switch (k)
	{
	case sf::Keyboard::Q:
		exists = false;

	default:
		break;
	}
}