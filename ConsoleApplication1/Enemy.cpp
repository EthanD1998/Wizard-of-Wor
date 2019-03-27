#include "pch.h"
#include "Enemy.h"

/*
	Im not commenting this class yet because it still needs a ton  of work
	-Justin		
*/

Enemy::Enemy(Map* _map = nullptr, std::vector<Entity*> *_entities = nullptr)
{
	color = sf::Color::Blue;
	
	value = 100;
	
	charScale = 2;
	charMove = 1;
	
	level = _map;
	entities = _entities;
	
	texture.loadFromFile("Sprites/Burwor.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f((rand() % 11 + 2) * 60, (rand() % 6 + 1) * 60));
	std::cout << "Spawned Enemy @ (" << sprite.getPosition().x / 60 << ", " << sprite.getPosition().y / 60 << ")\n";
	
	facing = rand() % 4;
}

Enemy::~Enemy()
{
	
}

std::string Enemy::type()
{
	return "Enemy";
}


void Enemy::handleEvents()
{
	switch(facing)
	{
		case N:
			velocity.y = -1 * charMove;
			sprite.setRotation(90);
			sprite.move(sf::Vector2f(0, -1 * charMove));
			break;
		case S:
			velocity.y = 1 * charMove;
			sprite.setRotation(270);
			sprite.move(sf::Vector2f(0, charMove));		
			break;
		case E:
			velocity.x = 1 * charMove;
			sprite.setScale(sf::Vector2f(charScale, -1 * charScale));
			sprite.setRotation(180);
			break;
		case W:
			velocity.x = -1 * charMove;
			sprite.setScale(charScale, charScale);
			sprite.setRotation(0);
			break;
		default:
			std::cout << "no direction " << facing << "\n";
	}
	sprite.move(sf::Vector2f(velocity.x * charMove, velocity.y * charMove));
	
	if(checkCollision())
	{
		sprite.move(sf::Vector2f(velocity.x * charMove * -2, velocity.y * charMove * -2));
		velocity = sf::Vector2f(0,0);
		newDirection();	
	}
	
	for(int i=0; i < entities->size(); i++)
	{
		if((entities->at(i)->type() == "Player") && sprite.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
		{
			if(entities->at(i)->killable)
			{
				Alive = false;
				entities->at(i)->Alive = false;
			}
		}
	}
	
	if(rand() % 300 == 1) shoot();
}

void Enemy::newDirection()
{
	int temp;
	while(temp == facing || temp > 3 || temp < 0)
	{
		temp = rand() % 4;
	}
	facing = temp;
}




