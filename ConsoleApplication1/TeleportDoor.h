#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>

class TeleportDoor : public Entity
{
	
public:

	TeleportDoor(map*,std::vector<Entity*>*);
	~TeleportDoor();
	void handleEvents() override;
	bool checkCollision() override;
	void checkFrameCount();
	void updateTexture();
	
	bool open = true;
	sf::Sprite second;
	int frameCount = 0;
	std::string type() override;

	void draw(sf::RenderWindow* target) override;
};

