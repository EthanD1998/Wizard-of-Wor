#include "pch.h"
#include "Thorwor.h"


Thorwor::Thorwor(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr)
{
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
	return "Thorwor";
}

Thorwor::~Thorwor()
{
}
