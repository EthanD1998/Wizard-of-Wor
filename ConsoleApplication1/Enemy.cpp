#include "pch.h"
#include "Enemy.h"

/*
	Im not commenting this class yet because it still needs a ton  of work
	-Justin		
*/

Enemy::Enemy()
{
	lastPos = getRelative();
	color = sf::Color::Transparent;

	value = 0;
	
	facing = rand() % 4;
	move();
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
	
	if(checkCollision())
	{
		sprite.move(sf::Vector2f(velocity.x * charMove * -2 * t, velocity.y * charMove * -2 * t));
		move();
		//velocity = sf::Vector2f(0, 0);
	}

	if (getRelative() != lastPos)
	{
		move();
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
}

void Enemy::move()
{	
	int x, y, t = rand() % 4;
	std::vector<int> openPaths;
	bool r = true;

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case N:
			x = 0;
			y = -1;
			break;
		case S:
			x = 0;
			y = 1;
			break;
		case E:
			x = 1;
			y = 0;
			break;
		case W:
			x = -1;
			y = 0;
			break;
		}
		sprite.move(sf::Vector2f(20 * x, 20 * y));
		if (!checkCollision())
		{
			std::cout << "Can move to " << i << "\n";
			openPaths.push_back(i);
		}
		sprite.move(sf::Vector2f(20 * x * -1, 20 * y * -1));
	}
	
	std::random_shuffle(openPaths.begin(), openPaths.end());

	while (r && t == facing)
	{
		t = rand() % 4;
		for (int i = 0; i < openPaths.size(); i++)
		{
			if (t == openPaths.at(i))
			{
				//std::cout << t << " == " << openPaths.at(i) << ", returning\n";
				facing = t;
				r = false;
			
			}
			else
			{
				t = facing;
			}	
		}

	}


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
