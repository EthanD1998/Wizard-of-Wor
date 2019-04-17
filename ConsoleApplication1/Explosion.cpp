#include "pch.h"
#include "Explosion.h"
#include "Entity.h"
#include <iostream>
#include <cmath>

Explosion::Explosion(sf::Vector2f pos)
{
	animation = AnimatedTexture(.15f, sf::Vector2f(43, 41), false);
	
	for(int i=1; i < 4 + 1; i++)
	{
		animation.addImage("Sprites/" + type() + "/" + type() + " (" + std::to_string(i) + ").png");
	}
	
	sprite.setTexture(animation);
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(pos);
}

Explosion::~Explosion()
{
}

std::string Explosion::type()
{
	return "Explosion";
}
	
void Explosion::handleEvents()
{
	animation.updateTexture();
	
	if(!animation.Alive)
	{
		Alive = false;
	}
}

void Explosion::draw(sf::RenderWindow* target)
{
	target->draw(sprite);
}
