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
	second.setString(" ");
	second.setCharacterSize(120);
	second.setFillColor(sf::Color::Yellow);
	textRect = second.getLocalBounds();
	second.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	second.setPosition(sf::Vector2f(425,400));
}


StartMenu::~StartMenu()
{
}

DisplayState* StartMenu::nextState()
{
	return new Game();
}

void StartMenu::keyEvent(sf::Keyboard::Key& k)
{
	switch(k)
	{
		case sf::Keyboard::Enter:
				if(!triggered)
				{
					triggered = true;	
					clock.restart();
				}
				
			break;
		default:
			break;
	}
}

void StartMenu::draw(sf::RenderWindow* target)
{
	target->draw(text);
	if(triggered)
	{
		target->draw(second);
	}
}

void StartMenu::updateEvents()
{
	if(triggered)
	{
		int temp = round(clock.getElapsedTime().asSeconds());
		if(temp > sec)
		{
			sec = temp;
		}
		
		switch(sec)
		{
			case 0:
			{
				font.loadFromFile("Fonts/AlienEncounters.ttf");
	
				second.setFont(font);
				text.setFont(font);
				text.setString("GET READY");
				text.setCharacterSize(100);
				text.setFillColor(sf::Color::Yellow);

				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				text.setPosition(sf::Vector2f(420,200));
			}
				break;
			
			case 2:
				second.setString("3");
				break;
				
			case 3:
				second.setString("2");
				break;
				
			case 4:
				second.setString("1");
				break;
				
			case 5:
				hasFocus = false;
				exists = false;
				break;
			default:
				break;
		}
	}
}

std::string StartMenu::type()
{
	return "StartMenu";
}

