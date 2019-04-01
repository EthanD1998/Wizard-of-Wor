#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Map* _map, int _facing = -1, int t = 0, std::vector<Entity*>* e = nullptr)
{
	team = t;
	
	entities = e;
	
	charScale = 1;
	charMove = 5;
	//The sprite scale and movement scale.  Both are ints.
	
	level = _map;
	//setting the map pointer
	
	texture.loadFromFile("Sprites/bullet.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	
	//sprite.setColor(sf::Color::Red);
	
	//set up the sprite & texture
	
	//This switch handles the rotation of the sprite depending on the direction it faces.
	switch(_facing)
	{
		case N:
			velocity.y = -1;
			sprite.setRotation(90);
			break;
		case S:
			velocity.y = 1;
			sprite.setRotation(90);			
			break;
		case E:
			velocity.x = 1;
			break;
		case W:
			velocity.x = -1;
			break;
	}
}


Bullet::~Bullet()
{
}

void Bullet::handleEvents()
{
	if(checkCollision()) Alive = false;
	//if the Bullet collides, it needs to die.
	
	sprite.move(sf::Vector2f(velocity.x * charMove, velocity.y * charMove));
	//move the sprite (dependent on the x / y velocity)
	for(int i=0; i < entities->size(); i++)
	{
		if((entities->at(i)->type().find("Enemy") != std::string::npos || entities->at(i)->type() == "Player") && sprite.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
		{
			if(entities->at(i)->killable && entities->at(i)->team != team)
			{
				Alive = false;
				entities->at(i)->Alive = false;
			}
		}
	}
}

std::string Bullet::type()
{
	return "Bullet" + std::to_string(team);
}
