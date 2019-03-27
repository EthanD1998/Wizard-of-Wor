#include "pch.h"
#include "SelectMenu.h"

SelectMenu::SelectMenu()
{
	std::cout << "DisplayState SelectMenu Created" << std::endl;
	/*
		Setting up both text objects	
	*/
	font.loadFromFile("Fonts/Adore.ttf");
		
	text.setFont(font);
	text.setString("ONE PLAYER");
	text.setCharacterSize(40);
	
	text.setFillColor(sf::Color::Yellow);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(425,200));
	
	
	second.setFont(font);
	second.setString("TWO PLAYERS");
	second.setCharacterSize(40);
	second.setFillColor(sf::Color::Blue);
	textRect = second.getLocalBounds();
	second.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	second.setPosition(sf::Vector2f(425,400));
	
	selectShape = sf::RectangleShape(sf::Vector2f(510, 10));
	selectShape.setFillColor(sf::Color::Red);
	//selectShape.setOrigin(selectShape.getLocalBounds().height / 2, selectShape.getLocalBounds().width / 2);
	selectShape.setPosition(sf::Vector2f(170, 230 + selected * 200));
	
	
}


SelectMenu::~SelectMenu()
{
}

DisplayState* SelectMenu::nextState()
{
	return new Game(1);
}

void SelectMenu::keyEvent(sf::Keyboard::Key& k)
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
		case sf::Keyboard::W:
			selected--;
			break;
		case sf::Keyboard::S:
			selected++;
			break;
		case sf::Keyboard::Q:
			exists = false;
		default:
			break;
	}
}

void SelectMenu::draw(sf::RenderWindow* target)
{
	target->draw(text);
	target->draw(second);
	if(!triggered) target->draw(selectShape);
}

void SelectMenu::updateEvents()
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

				second.setFont(font);
				second.setString(" ");
				second.setCharacterSize(120);
				second.setFillColor(sf::Color::Yellow);
				textRect = second.getLocalBounds();
				second.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				second.setPosition(sf::Vector2f(425, 400));
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
	else
	{
		if(selected < 0)
		{
			selected = 0;
		}
		else if(selected > 1)
		{
			selected = 1;
		}
		
		selectShape.setPosition(sf::Vector2f(170, 230 + selected * 200));
	}
}

std::string SelectMenu::type()
{
	return "SelectMenu";
}

