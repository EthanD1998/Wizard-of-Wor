#include "pch.h"
#include "Enemy.h"

/*
	Im not commenting this class yet because it still needs a ton  of work
	-Justin		
*/

Enemy::Enemy()
{
	color = sf::Color::Transparent;

	value = 0;
	
	facing = rand() % 4;

	current = getRelative();
	prev = current;
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
	current = getRelative();
	if(animation.Alive)
		animation.updateTexture();
	
	if(invisible)
		columnOpacity();
		
	int t = clock.getElapsedTime().asMilliseconds();
	
	
	switch(facing)
	{
		case N:
			velocity.y = -1 * charMove;
			sprite.setRotation(90);
			break;
		case S:
			velocity.y = 1 * charMove;
			sprite.setRotation(270);
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


	sprite.move(sf::Vector2f(velocity.x * charMove * t, velocity.y * charMove * t));
	
	if (current != prev)
	{
		int randNum = rand() % 10;
		if (randNum < 6)
		{
			facing;
		}
		else if (randNum > 7)
		{
			if (facing > 0)
				facing = facing - 1;
			else
				facing = 3;
		}
		else
		{
			if (facing < 3)
				facing = facing + 1;
			else
				facing = 0;
		}
		velocity = sf::Vector2f(0, 0);
	}


	if(checkCollision())
	{
		sprite.move(sf::Vector2f(velocity.x * charMove * -2 * t, velocity.y * charMove * -2 * t));
		velocity = sf::Vector2f(0, 0);
		newDirection();
	}

	
	for(int i=0; i < entities->size(); i++)
	{
		if(entities->at(i)->type().find("Player") != std::string::npos && sprite.getGlobalBounds().intersects(entities->at(i)->sprite.getGlobalBounds()))
		{
			//Alive = false;
			entities->at(i)->Alive = false;
		}
	}
	
	if(rand() % 350 == 1) shoot();
	
	clock.restart().asSeconds();
	prev = current;
}

void Enemy::columnOpacity()
{
	if(player->getPosition().x == getPosition().x)
	{
		sprite.setColor(sf::Color(255,255,255,255));
	}
	else
	{
		sprite.setColor(sf::Color(255,255,255,50));
	}
}

void Enemy::newDirection()
{
	int temp = -1;
	while(temp == facing || temp > 3 || temp < 0)
	{
		temp = rand() % 4;
	}
	facing = temp;
}
