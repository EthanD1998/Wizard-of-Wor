#include "StateManager.h"
#include <fstream>
#include <iostream>


StateManager::StateManager()
{
	std::cout << "StateManager Created" << std::endl;	
	
	gameStates.push_back(new StarBackground());
	gameStates.push_back(new StartMenu());
}

StateManager::~StateManager()
{
}

void StateManager::kill(int index)
{
	std::cout << "Killed DisplayState [" << gameStates.at(index)->type() << "] @ " << index << std::endl;
	gameStates.erase(gameStates.begin() + index);
}

void StateManager::init()
{
	sf::RenderWindow window(sf::VideoMode(840, 600), "Wizard of Wor [DEBUG]");
	window.setFramerateLimit(60);
	
	
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
		            
		        case sf::Event::KeyPressed:
		        {
		        	sf::Keyboard::Key j = event.key.code;
		        	switch(j)
		        	{
		        		case sf::Keyboard::W:
		        			//dont pass WASD, as it is checked in handleEvents.
		        			break;
		        		case sf::Keyboard::A:
		        			break;
		        		case sf::Keyboard::S:
		        			break;
		        		case sf::Keyboard::D:
		        			break;
		        		case sf::Keyboard::P:
		        			if(!isPaused())
		        			{
		        				for(int i=0; i < gameStates.size(); i++)
		        				{
		        					if(gameStates.at(i)->type() == "Game")
		        					{
		        						gameStates.at(i)->hasFocus = false;
		        						gameStates.at(i)->getsEvents = false;
		        						gameStates.push_back(new PauseMenu(gameStates.at(i)));
									}
								}
		        				
							}
		        		default:
		        			for(int i=0; i < gameStates.size(); i++)
		        			{
		        				if(gameStates.at(i)->hasFocus)
		        				{
		        					gameStates.at(i)->keyEvent(j);
								}
							}
							break;
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
				gameStates.push_back(gameStates.at(i)->nextState());
				kill(i);
			}
			
		}
		
		window.display();
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
