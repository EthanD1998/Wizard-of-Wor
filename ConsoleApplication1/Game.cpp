#include "pch.h"
#include "Game.h"

/*
	Game is where most of the flow is handled.		
*/

/*
	Creating the map and some starting entities.
*/
Game::Game(int index, int nextlevel, int playerLives)
{
	enum {
		burwor, garwor, thorwor
	};
	
	nextlvl = nextlevel;
	
	gameLevel = index;
	
	std::cout << "DisplayState Game Created" << std::endl;
	level = Map("level_" + std::to_string(nextlvl) + ".csv");
	
	player = new Player(&level,&entities, playerLives);
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
	
	for(int i=0; i < level.getProperty(burwor); i++)
	{
		entities.push_back(new Burwor(&level, &entities));
		//Makes 6 enemies
	}
	for(int i=0; i < level.getProperty(garwor); i++)
	{
		entities.push_back(new Garwor(&level, &entities, player));
	}
	for(int i=0; i < level.getProperty(thorwor); i++)
	{
		entities.push_back(new Thorwor(&level, &entities, player));
	}
}

std::string Game::type()
{
	return "Game";
}

Game::~Game()
{
}

int Game::findEntity(std::string target)
{
	for(int i=0; i < entities.size(); i++)
	{
		if(entities.at(i)->type().find(target) != std::string::npos)
			return i;
	}
	return -1;
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
			entities.at(index)->link->Alive = false;
			entities.erase(entities.begin() + index);
			entities.shrink_to_fit();
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
	if(player->lives == 0 || findEntity("Enemy") == -1)
	{
		exists = false;
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
		entities.push_back(new Burwor(&level, &entities));
		break;
	case sf::Keyboard::E:
		//kill all enemies
		for(int i = entities.size() - 1; i >= 0; i--)
		{
			if(entities.at(i)->type().find("Enemy") != std::string::npos)
			{
				kill(i);	
			}
		}
		break;
	case sf::Keyboard::Space:
		player->shoot();
		break;
	case sf::Keyboard::I:
		player->killable = false;
		break;
			
	}
}

DisplayState* Game::nextState()
{
	int nextLevel = 1;
	if(player->lives == 0) return new ScoreMenu();
	gameLevel++;
	
	do
	{
		if (gameLevel > 7)
		{
			if ((gameLevel - 13) % 6 == 0)
				nextLevel = 25;
			else
				nextLevel = rand() % 8 + 16; // this number is based on how many we have done
		}
		else
		{
			if (gameLevel == 4)
				nextLevel = 24;
			else
				nextLevel = rand() % 2 + 1; // this number is based on how many we have done
		}
	} while (nextlvl == nextLevel);
	
	return new Game(gameLevel, nextLevel, player->lives); //increment this
}

bool Game::outsideMap(Entity* e)
{
	sf::Vector2f pos = e->sprite.getPosition();
	
	if(pos.x > 850 || pos.x < 0 || pos.y > 600 || pos.y < 0) return true;
	return false;
}

