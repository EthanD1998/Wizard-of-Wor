#include "pch.h"
#include "Wizard.h"


Wizard::Wizard(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr, Entity* p = nullptr)
{
	invisible = false;

	player = p;


	value = 2500;

	charScale = 2;
	charMove = .45;
	shootChance = 50;

	level = _map;
	entities = _entities;


	animation = AnimatedTexture(.1f, sf::Vector2f(20, 20), true);

	for (int i = 1; i < 4 + 1; i++)
	{
		animation.addImage("Sprites/Wizard.png");
	}

	sprite.setTexture(animation);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f((rand() % 11 + 2) * 60, (rand() % 6 + 1) * 60));
	std::cout << "Spawned Wizard @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";

	facing = rand() % 4;
}


std::string Wizard::type()
{
	return "Enemy Wizard";
}


Wizard::~Wizard()
{
}
