#include "pch.h"
#include "Game.h"

/*
	Game is where most of the flow is handled.		
*/

/*
	Creating the map and some starting entities.
*/
Game::Game(int index)
{
	std::cout << "DisplayState Game Created" << std::endl;
	level = Map("level_" + std::to_string(index) + ".csv");
	
	player = new Player(&level,&entities);
	entities.push_back(player);
	
	sf::RectangleShape s(sf::Vector2f(286,156));
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(2);
	s.setPosition(sf::Vector2f(282, 410));
	shapes.push_back(s);
	//the radar outline box

	entities.push_back(new TeleportDoor(&level, &entities));
	entities.push_back(new TrapDoor(&level, &entities));
	
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
	if(entities.at(index)->killable)
	{
		entities.at(index)->lives--;
	
		if (entities.at(index)->lives == 0)
		{
			std::cout << "Killed Entity [" << entities.at(index)->type() << "] @ " << index << std::endl;
			player->score += entities.at(index)->value;
			//add the entities's worth to the player's score
			entities.erase(entities.begin() + index);
		}
		else
		{
			entities.push_back(new TrapDoor(&level, &entities));
			entities.at(index)->Alive = true;
			entities.at(index)->respawn();
			std::cout << "Removed 1 life from [" << entities.at(index)->type() << "], " << entities.at(index)->lives << " lives left." << std::endl;
		}
	}
	else
	{
		entities.at(index)->Alive = true;
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
	case sf::Keyboard::O:
		//respawn player
		entities.push_back(new Player(&level, &entities));
		break;
	case sf::Keyboard::Space:
		player->shoot();
		break;
	}
}

DisplayState* Game::nextState()
{
//	return new GameOver();
//TODO: Add GameOver screen
	return new StartMenu();
}

bool Game::outsideMap(Entity* e)
{
	sf::Vector2f pos = e->sprite.getPosition();
	
	if(pos.x > 850 || pos.x < 0 || pos.y > 600 || pos.y < 0) return true;
	return false;
}

