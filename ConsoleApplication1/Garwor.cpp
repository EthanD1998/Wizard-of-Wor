#include "pch.h"
#include "Garwor.h"


Garwor::Garwor(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr)
{
	color = sf::Color::Yellow;

	value = 200;

	charScale = 2;
	charMove = 1;

	level = _map;
	entities = _entities;

	texture.loadFromFile("Sprites/Garwor.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f((rand() % 11 + 2) * 60, (rand() % 6 + 1) * 60));
	std::cout << "Spawned Enemy @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";

	facing = rand() % 4;
}

std::string Garwor::type()
{
	return "Garwor";
}

Garwor::~Garwor()
{
}
