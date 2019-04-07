#include "pch.h"
#include "Burwor.h"

Burwor::Burwor(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr)
{
	value = 100;

	charScale = 2;
	charMove = .25;

	level = _map;
	entities = _entities;

	texture.loadFromFile("Sprites/Burwor.png");

	animation = AnimatedTexture(.15f, sf::Vector2f(20,20), true);
	
	for(int i = 1; i < 5; i++)
	{
		animation.addImage("Sprites/Burwor/Burwor (" + std::to_string(i) + ").png");
	}

	sprite.setTexture(animation);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f((rand() % 11 + 2) * 60, (rand() % 6 + 1) * 60));
	std::cout << "Spawned Enemy @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";

	facing = rand() % 4;
}


Burwor::~Burwor()
{
}

std::string Burwor::type()
{
	return "Enemy Burwor"; 
}
