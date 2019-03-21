#include "pch.h"
#include "PauseMenu.h"

/*
	Setting up shapes
*/
PauseMenu::PauseMenu(DisplayState* g)
{
	game = g;
	hasFocus = false;
	std::cout << "DisplayState PauseMenu Created" << std::endl;
	
	font.loadFromFile("Fonts/AlienEncounters.ttf");
		
	text.setFont(font);
	text.setString("PAUSED");
	text.setCharacterSize(100);
	
	text.setFillColor(sf::Color::White);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(425,300));
	
	rect.setFillColor(sf::Color(0,0,0,150));
	rect.setSize(sf::Vector2f(850,600)); //screen dimensions
	rect.setPosition(sf::Vector2f(0,0));
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw(sf::RenderWindow* target)
{
	target->draw(rect);
	target->draw(text);
	hasFocus = true;
	//drawing stuff
}	

void PauseMenu::keyEvent(sf::Keyboard::Key& k)
{
	switch(k)
	{
		case sf::Keyboard::P:
			exists = false;
			game->hasFocus = true;
			game->getsEvents = true;
			break;
		default:
			break;
	}
}

std::string PauseMenu::type()
{
	return "PauseMenu";
}

