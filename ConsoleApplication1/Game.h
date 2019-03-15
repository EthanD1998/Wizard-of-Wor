#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "TeleportDoor.h"




typedef std::vector<std::vector<std::vector<sf::RectangleShape>>> Map;

class Game
{
public:
	Game();
	~Game();
	

	//Player p;
	void drawMap(sf::RenderWindow*);
	void populateMap();
	void handleGameEvents(sf::RenderWindow* window);
	void init();
	void kill(int);
	bool outsideMap(Entity*);
	bool bulletExists();
	
	int frameCount = 0;
	std::vector<sf::RectangleShape> shapes;
	std::vector<Entity*> entities;
	Map map;
};

