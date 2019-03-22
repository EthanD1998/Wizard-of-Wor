#include "pch.h"
#include "StartMenu.h"

StartMenu::StartMenu()
{
	std::cout << "DisplayState StartMenu Created" << std::endl;
	/*
		Setting up both text objects	
	*/
	font.loadFromFile("Fonts/Adore.ttf");
		
	text.setFont(font);
	text.setString("PRESS ENTER TO START");
	text.setCharacterSize(24);
	
	text.setFillColor(sf::Color::Red);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(425,400));
	
	
	second.setFont(font);
	second.setString("Wizard Of Wor");
	second.setCharacterSize(60);
	second.setFillColor(sf::Color::Blue);
	textRect = second.getLocalBounds();
	second.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	second.setPosition(sf::Vector2f(425,200));
}


StartMenu::~StartMenu()
{
}

DisplayState* StartMenu::nextState()
{
	return new SelectMenu();
}

void StartMenu::keyEvent(sf::Keyboard::Key& k)
{
	switch(k)
	{
		case sf::Keyboard::Enter:
				exists = false;
		default:
			break;
	}
}

void StartMenu::draw(sf::RenderWindow* target)
{
	target->draw(text);
	target->draw(second);
}

std::string StartMenu::type()
{
	return "StartMenu";
}

