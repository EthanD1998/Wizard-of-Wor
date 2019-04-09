#include "pch.h"
#include "Garwor.h"


Garwor::Garwor(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr, Entity* p = nullptr)
{
	invisible = true;
	
	player = p;
	
	color = sf::Color::Yellow;

	value = 200;

	charScale = 2;
	charMove = .25;

	level = _map;
	entities = _entities;

	//texture.loadFromFile("Sprites/Garwor.png");
	animation = AnimatedTexture(.1f, sf::Vector2f(20,20), true);
	
	for(int i = 1; i < 4 + 1; i++)
	{
		animation.addImage("Sprites/Garwor/Garwor (" + std::to_string(i) + ").png");
	}
	
	sprite.setTexture(animation);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f((rand() % 11 + 2) * 60, (rand() % 6 + 1) * 60));
	//std::cout << "Spawned Enemy @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";

	facing = rand() % 4;
}

std::string Garwor::type()
{
	return "Enemy Garwor";
}

Garwor::~Garwor()
{
}
