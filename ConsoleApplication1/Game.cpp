#include "pch.h"
#include "Game.h"

/*
	Game is where most of the flow is handled.		
*/

	/*
		Creating the map and some starting entities.
	*/
Game::Game()
{
	std::cout << "DisplayState Game Created" << std::endl;

	level = map("level_1.csv");
	
	entities.push_back(new Player(&level));
	
	sf::RectangleShape s(sf::Vector2f(286,156));
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(2);
	s.setPosition(sf::Vector2f(282, 410));
	shapes.push_back(s);
	//the radar outline box

	entities.push_back(new TeleportDoor(&level, &entities));
	
	for(int i=0; i < 6; i++)
	{
		entities.push_back(new Enemy(&level, &entities));
		//Makes 6 enemies
	}
	
}

std::string Game::type()
{
	return "Game";
}

Game::~Game()
{
	
}

void Game::kill(int index)
{
	entities.at(index)->lives--;

	if (entities.at(index)->lives == 0)
	{
		std::cout << "Killed Entity [" << entities.at(index)->type() << "] @ " << index << std::endl;
		entities.erase(entities.begin() + index);
	}
	else
	{
		entities.at(index)->Alive = true;
		entities.at(index)->respawn();
		std::cout << "Removed 1 life from [" << entities.at(index)->type() << "], " << entities.at(index)->lives << " lives left." << std::endl;
	}
}


/*
	Loops through the vector of entities and shapes and draws them all.		
*/
void Game::draw(sf::RenderWindow* target)
{
	target->draw(level);
	
	for(int i=0; i < entities.size(); i++)
	{
		if(entities.at(i)->Alive && !outsideMap(entities.at(i)))
		{
			entities.at(i)->draw(target);
		}
		else
		{
			kill(i);
		}
	}
	
	for(int i=0; i < shapes.size(); i++)
	{
		target->draw(shapes.at(i));
	}
	
}

void Game::updateEvents()
{
	//clock for the respawn timer to be implemented (maybe)
	
	for(int i=0; i < entities.size(); i++)
	{
		if(entities.at(i)->Alive && !outsideMap(entities.at(i)))
		{
			entities.at(i)->handleEvents();
		}
		else
		{
			kill(i);
		}
	}
}
/*
	Most of these are helpful in debug.
	They will be remove in production.	
*/
void Game::keyEvent(sf::Keyboard::Key& k)
{
	switch (k)
	{
	case sf::Keyboard::Q:
		//spawn new enemy
		entities.push_back(new Enemy(&level, &entities));
		break;
	case sf::Keyboard::E:
		//kill all enemies
		for(int i = entities.size() - 1; i >= 0; i--)
		{
			if(entities.at(i)->type() == "Enemy")
			{
				kill(i);	
			}
		}
		
		break;
	case sf::Keyboard::R:
		//re-open doors
		for(int i = entities.size() - 1; i > 0; i--)
		{
			if(entities.at(i)->type().find("Door") != std::string::npos)
			{
				kill(i);	
			}
		}
				
		entities.push_back(new TeleportDoor(&level, &entities));
		break;
	case sf::Keyboard::O:
		//respawn player
		entities.push_back(new Player(&level));
		break;
	case sf::Keyboard::Space:
		//shoot a bullet
		if (!bulletExists())
		{
			for (int i = 0; i < entities.size(); i++)
			{
				if (entities.at(i)->type() == "Player")
				{
					entities.push_back(new Bullet(&level, entities.at(i)->facing));
					entities.at(entities.size() - 1)->sprite.setPosition(entities.at(i)->sprite.getPosition());
				}
			}
		}
		break;
	}
}

bool Game::bulletExists()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities.at(i)->type() == "Bullet")
		{
			return true;
		}
	}
	return false;
}

DisplayState* Game::nextState()
{
	return new StartMenu();
}

bool Game::outsideMap(Entity* e)
{
	sf::Vector2f pos = e->sprite.getPosition();
	
	if(pos.x > 850 || pos.x < 0 || pos.y > 600 || pos.y < 0) return true;
	return false;
}

