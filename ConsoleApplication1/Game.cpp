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
	populateMap();
	
	entities.push_back(new Player(&map));
	
	sf::RectangleShape s(sf::Vector2f(286,156));
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(2);
	s.setPosition(sf::Vector2f(282, 410));
	shapes.push_back(s);
	//the radar outline box

	entities.push_back(new TeleportDoor(&entities));
	
	for(int i=0; i < 6; i++)
	{
		entities.push_back(new Enemy(&map, &entities));
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
	std::cout << "Killed Entity [" << entities.at(index)->type() << "] @ " << index << std::endl;
	entities.erase(entities.begin() + index);
}


/*
	Loops through the vector of entities and shapes and draws them all.		
*/
void Game::draw(sf::RenderWindow* target)
{
	drawMap(target);
	
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
		entities.push_back(new Enemy(&map, &entities));
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
				
		entities.push_back(new TeleportDoor(&entities));
		break;
	case sf::Keyboard::O:
		//respawn player
		entities.push_back(new Player(&map));
		break;
	case sf::Keyboard::Space:
		//shoot a bullet
		if (!bulletExists())
		{
			for (int i = 0; i < entities.size(); i++)
			{
				if (entities.at(i)->type() == "Player")
				{
					entities.push_back(new Bullet(entities.at(i)->facing, &map));
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

void Game::drawMap(sf::RenderWindow* target)
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				target->draw(map.at(i).at(j).at(k));
			}

		}
	}
}

bool Game::outsideMap(Entity* e)
{
	sf::Vector2f pos = e->sprite.getPosition();
	
	if(pos.x > 850 || pos.x < 0 || pos.y > 600 || pos.y < 0) return true;
	return false;
}

void Game::populateMap()
{
	std::ifstream file("Levels/level_1.csv");
	std::string value;
	
	//resizing the vector to what we need.
	//will be removed with the addition of the Map class.
	
	map.resize(13);
	for (int j = 0; j < 13; j++)
	{
		map.at(j).resize(7);

		for (int k = 0; k < 7; k++)
		{
			map.at(j).at(k).resize(4);
		}
	}


	while (file.good())
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					getline(file, value, ',');
					
					/*
						read the fstream, and look for a 1.
							If we see a 1, there is a wall there.
							Might be more numbers later.
					*/
					if (value.find("1") != std::string::npos)
					{
						sf::RectangleShape s(sf::Vector2f(60, 5));
						s.setPosition(sf::Vector2f(60 + (60 * i), 60 + (60 * j)));
						s.setOrigin(sf::Vector2f(30, 30));
						s.setRotation((k * 90));
						s.setFillColor(sf::Color::Blue);
						
						map.at(i).at(j).at(k) = s;
					}
					
					//Very rudimentary solution to put a transparent wall at the door location.
					//relocate this ASAP.
					if((i == 1 && j == 2 && k == 3) || (i == 11 && j == 2 && k == 1))
						{
						sf::RectangleShape s(sf::Vector2f(60, 5));
						s.setPosition(sf::Vector2f(60 + (60 * i), 60 + (60 * j)));
						s.setOrigin(sf::Vector2f(30, 30));
						s.setRotation((k * 90));
						s.setFillColor(sf::Color::Transparent);
						map.at(i).at(j).at(k) = s;
						}
				}
			}
		}
	}
}
