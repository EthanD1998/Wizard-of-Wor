#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>

class TeleportDoor : public Entity
{
	
public:

	TeleportDoor(std::vector<Entity*>*);
	~TeleportDoor();
	void handleEvents() override;
	bool checkCollision() override;
	void checkFrameCount();
	void updateTexture();
	
	bool open = true;

	sf::Sprite second;
	int frameCount = 0;
	std::string type() override;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

