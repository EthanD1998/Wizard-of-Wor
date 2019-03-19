#include "StateManager.h"
#include <fstream>
#include <iostream>


StateManager::StateManager()
{
	std::cout << "StateManager Created" << std::endl;	
	
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
	sf::RenderWindow window(sf::VideoMode(850, 600), "Wizard of Wor [DEBUG]");
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
		        	if(j != sf::Keyboard::W && j != sf::Keyboard::A && j != sf::Keyboard::S && j != sf::Keyboard::D)
		        	{
		        		for(int i=0; i < gameStates.size(); i++)
		        		{
		        			if(gameStates.at(i)->hasFocus)
		        			{
		        				gameStates.at(i)->keyEvent(j);
							}
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
			if(gameStates.at(i)->exists)
			{
				gameStates.at(i)->updateEvents();
				gameStates.at(i)->draw(&window);
			}
			else
			{
				gameStates.push_back(gameStates.at(i)->nextState());
				kill(i);
				break;
			}
		}
		
		window.display();
	}
}

