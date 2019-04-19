#include "pch.h"
#include "IntermediateState.h"


IntermediateState::IntermediateState(int index, int nextLevel, int pCount, std::vector<int> playerProp, bool doubleDungeon, Map lev)
{
	level = lev;
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
	text.setFillColor(sf::Color::Yellow);
	textRect = second.getLocalBounds();
	second.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	second.setPosition(sf::Vector2f(425, 300));
	second.setFillColor(sf::Color::Yellow);


	for (int i = 0; i < 10; i++)
	{
		colors.push_back(HSLtoRGB(sf::Color(rand() % 360, 100, 50)));
	}

	clearColor = sf::Color::Black;
}


IntermediateState::~IntermediateState()
{

}


void IntermediateState::updateEvents()
{
	if (scoreDouble)
	{
		sf::Image a;
		int r;
		a.create(60, 5);
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				r = rand() % 255;
				a.setPixel(i, j, sf::Color(255, r, 0));
			}
		}
		level.setTex(a);
	}
}

sf::Color IntermediateState::HSLtoRGB(sf::Color col) {

	double C = 2 * col.b*col.g;
	double Hprime = col.r / 60.0;
	double a = Hprime - 2 * floor(Hprime / 2.0);
	double X = C * (1 - fabs(a - 1));
	double C_0 = C * 255;
	double X_0 = X * 255;

	if (Hprime >= 0 && Hprime < 1) {
		col.r = C_0;
		col.g = X_0;
		col.b = 0;
	}
	if (Hprime >= 1 && Hprime < 2) {
		col.r = X_0;
		col.g = C_0;
		col.b = 0;
	}
	if (Hprime >= 2 && Hprime < 3) {
		col.r = 0;
		col.g = C_0;
		col.b = X_0;
	}
	if (Hprime >= 3 && Hprime < 4) {
		col.r = 0;
		col.g = X_0;
		col.b = C_0;
	}
	if (Hprime >= 4 && Hprime < 5) {
		col.r = X_0;
		col.g = 0;
		col.b = C_0;
	}
	if (Hprime >= 5 && Hprime < 6) {
		col.r = C_0;
		col.g = 0;
		col.b = X_0;
	}

	return col;


}

DisplayState* IntermediateState::nextState()
{
	return new Game(gameIndex, nextGameLevel, gamePCount, gamePlayerProp, scoreDouble);
}


void IntermediateState::draw(sf::RenderWindow *target)
{
	if (scoreDouble)
	{
		if (rand() % 4 == 1)
		{
			clearColor = HSLtoRGB(sf::Color(rand() % 360, 100, 50)); //colors.at(rand() % colors.size());
		}
		target->clear(clearColor);
	}


	target->draw(level);
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
