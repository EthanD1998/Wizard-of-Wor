#include "pch.h"
#include "FpsCounter.h"

FpsCounter::FpsCounter()
{
	font.loadFromFile("Fonts/Adore.ttf");
		
	text.setFont(font);
	text.setString("10");
	text.setCharacterSize(25);
	
	text.setFillColor(sf::Color::White);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(30,20));
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::updateEvents()
{
	if(clock.getElapsedTime().asSeconds() >= 1.f)
		{
			frame = sec;
			sec = 0;
			clock.restart();
		}
		++sec;
		text.setString(std::to_string(frame));
}

void FpsCounter::draw(sf::RenderWindow* target)
{
	target->draw(text);
}

std::string FpsCounter::type()
{
	return "FpsCounter";
}

