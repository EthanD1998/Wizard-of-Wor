#include "pch.h"
#include "Game.h"

/*
	Game is where most of the flow is handled.		
*/

/*
	Creating the map and some starting entities.
*/
Game::Game(int index, int nextlevel, int pCount, std::vector<int> playerProp, bool doubleDungeon)
{
	sf::FloatRect textRect;
	playerCount = pCount;
	
	nextlvl = nextlevel;
	
	gameLevel = index;
	if (index > 6)
		enemyNum = 6;
	else
		enemyNum = index;

	if (doubleDungeon)
		scoreMulti = 2;
	std::cout << "DisplayState Game Created" << std::endl;
	
	level = Map("level_" + std::to_string(nextlvl) + ".csv");
	
	player = new Player(&level,&entities, playerProp.at(0), playerProp.at(1), 0);
	entities.push_back(player);
		
	if(playerCount > 1)
	{
		playerTwo = new Player(&level,&entities, playerProp.at(2), playerProp.at(3), 1);
		entities.push_back(playerTwo);
	}
	
	sf::RectangleShape s(sf::Vector2f(286,156));
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(2);
	s.setPosition(sf::Vector2f(282, 410));
	shapes.push_back(s);
	//the radar outline box

	entities.push_back(new TeleportDoor(&level, &entities));
	entities.push_back(new TrapDoor(&level, &entities, 0));
	entities.push_back(new TrapDoor(&level, &entities, 1));	
	
	for (int i = 0; i < 6; i++)
	{
		entities.push_back(new Burwor(&level, &entities));
		//Makes 6 enemies
	}

	font.loadFromFile("Fonts/Adore.ttf");
	dungeonLevel.setFont(font);
	dungeonLevel.setString("Dungeon " + std::to_string(gameLevel));
	if (gameLevel == 4)
		dungeonLevel.setString("The Arena");
	if ((gameLevel - 13) % 6 == 0 && gameLevel >= 13)
		dungeonLevel.setString("The Pit");
	textRect = dungeonLevel.getLocalBounds();
	dungeonLevel.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	dungeonLevel.setPosition(sf::Vector2f(shapes.at(0).getPosition().x + shapes.at(0).getSize().x / 2, shapes.at(0).getPosition().y - 10));
	dungeonLevel.setScale(sf::Vector2f(.5, .5));
	dungeonLevel.setFillColor(sf::Color::Red);

}

std::string Game::type()
{
	return "Game";
}

Game::~Game()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->type().find("Player") == std::string::npos)
			delete entities.at(i);
	}
	if (player != nullptr)
		delete player;
	if (playerTwo != nullptr)
		delete playerTwo;
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

void Game::spawnEnemies(std::string entityName)
{
	bool isEnemy = false;
	if (entityName == "Enemy Burwor")
	{
		if (enemyNum > 0)
		{
			enemyNum--;
			entities.push_back(new Garwor(&level, &entities, player));
		}
	}
	else if (entityName == "Enemy Garwor")
	{
		entities.push_back(new Thorwor(&level, &entities, player));
	}
	else
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities.at(i)->type().find("Enemy") != std::string::npos)
				isEnemy = true;
		}
		if (!isEnemy && !worlukSpawned)
		{
			entities.push_back(new Worluk(&level, &entities, player));
			worlukSpawned = true;
		}
		if (!isEnemy && worlukSpawned && !wizardSpawned && gameLevel > 1)
		{
			wizardSpawned = true;
			if (rand() % 8 == 0)
				entities.push_back(new Wizard(&level, &entities, player));
		}
	}
}

void Game::kill(int index)
{
	Entity* e = entities.at(index);
	std::string tempEName;
	
	if(e->type().find("Enemy") != std::string::npos || e->type().find("Player") != std::string::npos)
	{
		entities.push_back(new Explosion(e->sprite.getPosition()));
	}
	
	if (e->killable)
	{
		e->lives--;

		if (e->lives == 0)
		{
			std::cout << "Killed Entity [" << e->type() << "] @ " << index << " with score: " << e->value << std::endl;
			if (e->value != 0)
			{
				if(player->team == e->killedBy)
				{
					player->score += e->value * scoreMulti;
				}
				else if(playerCount > 1 && playerTwo->team == e->killedBy)
				{
					playerTwo->score += e->value * scoreMulti;
				}
				
			}
			if (e->killedBy != -1 && e->type().find("Worluk") != std::string::npos)
				worlukKilled = true;
			e->link->Alive = false;
			
			tempEName = entities.at(index)->type();
			if (e->type().find("Player") == std::string::npos)
				delete e;
			
			entities.erase(entities.begin() + index);
			entities.shrink_to_fit();
			spawnEnemies(tempEName);

		}
		else
		{
			entities.push_back(new TrapDoor(&level, &entities, e->team));
			e->Alive = true;
			e->respawn();
			std::cout << "Removed 1 life from [" << e->type() << "], " << e->lives << " lives left." << std::endl;
		}
	}
	else
	{
		e->Alive = true;
	}
}


/*
	Loops through the vector of entities and shapes and draws them all.		
*/
void Game::draw(sf::RenderWindow* target)
{
	target->draw(level);
	target->draw(dungeonLevel);



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
	if (player->lives <= 0 || findEntity("Enemy") == -1 || (playerCount > 1 && playerTwo->lives == 0))
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
		//player->shoot();
		break;
	case sf::Keyboard::K:
		player->lives = 0;
		break;
	case sf::Keyboard::C:
		player->score += 10000;
		break;
	case sf::Keyboard::I:
		player->killable = false;
		break;
			
	}
}

DisplayState* Game::nextState()
{
	std::vector<int> prop;
	
	if (((gameLevel - 13) % 6 == 0  && gameLevel >= 13) || gameLevel == 4)
	{
		if (player->lives > 0 && player->lives < 5)
			player->lives++;
		if (playerCount > 1)
		{
			if (playerTwo->lives > 0 && playerTwo->lives < 5)
				playerTwo->lives++;
		}
	}

	prop.push_back(player->lives);
	prop.push_back(player->score);
	
	if(playerCount > 1)
	{
	prop.push_back(playerTwo->lives);
	prop.push_back(playerTwo->score);
	}
	
	int nextLevel = 1;
	if(player->lives <= 0)
	{
		if(playerCount > 1)
		{
			return new ScoreMenu(player->score,playerTwo->score); //, playerTwo->score);
		}
		return new ScoreMenu(player->score); //, playerTwo->score);
	}
	
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
	
	return new IntermediateState(gameLevel, nextLevel, playerCount, prop, worlukKilled); //increment this
}

bool Game::outsideMap(Entity* e)
{
	sf::Vector2f pos = e->sprite.getPosition();
	
	if(pos.x > 850 || pos.x < 0 || pos.y > 600 || pos.y < 0) return true;
	return false;
}

