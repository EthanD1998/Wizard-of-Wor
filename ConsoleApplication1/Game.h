#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "DisplayState.h"

#include "Entity.h"
//#include "Entity.cpp"

#include "Player.h"
//#include "Player.cpp"

#include "Bullet.h"
//#include "Bullet.cpp"

#include "Enemy.h"
//#include "Enemy.cpp"

#include "TeleportDoor.h"
//#include "TeleportDoor.cpp"


typedef std::vector<std::vector<std::vector<sf::RectangleShape>>> Map;

class Game : public DisplayState
{
public:
	Game();
	~Game();
	
	void updateEvents() override;
	void draw(sf::RenderWindow*) override;
	void keyEvent(sf::Keyboard::Key&) override;
	std::string type() override;


	void drawMap(sf::RenderWindow*);
	void populateMap();
	void kill(int);
	bool outsideMap(Entity*);
	bool bulletExists();
	
	int frameCount = 0;
	std::vector<sf::RectangleShape> shapes;
	std::vector<Entity*> entities;
	Map map;
};

