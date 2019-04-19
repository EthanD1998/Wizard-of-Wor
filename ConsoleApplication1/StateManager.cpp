#include "pch.h"
#include "StateManager.h"
#include <fstream>
#include <iostream>

StateManager::StateManager()
{
	std::cout << "StateManager Created" << std::endl;	
	
	gameStates.push_back(new StarBackground());
	gameStates.push_back(new StartMenu());
	gameStates.push_back(new FpsCounter());

	for (int i = 0; i < 10; i++)
	{
		keys.push_back(sf::Keyboard::T);
	}

}

StateManager::~StateManager()
{
	for (int i = 0; i < gameStates.size(); i++)
	{
		delete gameStates.at(i);
	}
}

void StateManager::kill(int index)
{
	std::cout << "Killed DisplayState [" << gameStates.at(index)->type() << "] @ " << index << std::endl;
	delete gameStates.at(index);
	gameStates.erase(gameStates.begin() + (index));
	gameStates.shrink_to_fit();
}

void StateManager::init()
{
	sf::ContextSettings settings;
	sf::View view;

	settings.antialiasingLevel = 1;
	sf::RenderWindow window(sf::VideoMode(840, 600), "Wizard of Wor [DEBUG]", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(240);

	view.reset(sf::FloatRect(0, 0, 840, 600));
	window.setView(view);
	
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
		    switch (event.type)
		    {
		        case sf::Event::Closed:
		            window.close();
		            break;
		        case sf::Event::LostFocus:
		        	pause();
		        	break;
		        case sf::Event::TextEntered:
		        	{
		        	for(int i=0; i < gameStates.size(); i++)
		        	{
		        		if(gameStates.at(i)->hasFocus && event.text.unicode != 8)
		        		{
		        			gameStates.at(i)->input(event.text);
						}
					}
					}
					break;
		        case sf::Event::KeyPressed:
		        {
		        	sf::Keyboard::Key j = event.key.code;
		        	switch(j)
		        	{
		        		case sf::Keyboard::P:
		        			if(!isPaused())
		        			{
		        				pause();
							}
							break;
		        		default:
							keys.push_back(j);
							if (konami())
							{
								view.rotate(180);
								window.setView(view);
							}
							break;
					}
		        	for(int i=0; i < gameStates.size(); i++)
		        	{
		        		if(gameStates.at(i)->hasFocus)
		        		{
		        			gameStates.at(i)->keyEvent(j);
						}
					}
				}
		    		break;
		            
		        default:
		            break;
		    }
		}
		
		window.clear();
		for(int i=0; i < gameStates.size(); i++)
		{
			gameStates.at(i)->draw(&window);
			
			if(gameStates.at(i)->getsEvents)
			{
				gameStates.at(i)->updateEvents();
			}
			
			if(!gameStates.at(i)->exists)
			{
				if(gameStates.at(i)->hasNext)
				{
					gameStates.push_back(gameStates.at(i)->nextState());
				}
				kill(i);
			}
			
		}
		
		window.display();
	}
}

bool StateManager::konami()
{
	keys.erase(keys.begin());
	if ((keys.at(0) == sf::Keyboard::Up && keys.at(1) == sf::Keyboard::Up) &&
		(keys.at(2) == sf::Keyboard::Down && keys.at(3) == sf::Keyboard::Down) &&
		(keys.at(4) == sf::Keyboard::Left && keys.at(5) == sf::Keyboard::Left) &&
		(keys.at(6) == sf::Keyboard::Right && keys.at(7) == sf::Keyboard::Right) &&
		(keys.at(8) == sf::Keyboard::Space && keys.at(9) == sf::Keyboard::M))
	{
		return true;
	}
	return false;
}

void StateManager::pause()
{
	for(int i=0; i < gameStates.size(); i++)
	{
		if(gameStates.at(i)->type() == "Game")
		{
			gameStates.at(i)->hasFocus = false;
			gameStates.at(i)->getsEvents = false;
			gameStates.push_back(new PauseMenu(gameStates.at(i)));
			break;
		}
	}
}

bool StateManager::isPaused()
{
	for(int i=0; i < gameStates.size(); i++)
	{
		if(gameStates.at(i)->type() == "PauseMenu") return true;
	}
	return false;
}
