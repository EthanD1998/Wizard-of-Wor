#include "pch.h"
#include "Thorwor.h"


Thorwor::Thorwor(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr, Entity* p = nullptr)
{
	player = p;
	color = sf::Color::Red;

	value = 500;

	charScale = 2;
	charMove = 1;

	level = _map;
	entities = _entities;

	texture.loadFromFile("Sprites/Thorwor.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f((rand() % 11 + 2) * 60, (rand() % 6 + 1) * 60));
	std::cout << "Spawned Thorwor @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";

	facing = rand() % 4;
}

std::string Thorwor::type()
{
	return "Enemy Thorwor";
}

void Thorwor::columnOpacity()
{
	if(player->getPosition().x == getPosition().x)
	{
		sprite.setColor(sf::Color(255,255,255,255));
	}
	else
	{
		sprite.setColor(sf::Color(255,255,255,0));
	}
}

Thorwor::~Thorwor()
{
}
