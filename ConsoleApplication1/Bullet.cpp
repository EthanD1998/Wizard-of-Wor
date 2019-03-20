#include "Bullet.h"


Bullet::Bullet(int _facing = -1, Map* _map = nullptr)
{
	charScale = 1;
	charMove = 5;
	
	map = _map;
	
	if (!texture.loadFromFile("Sprites/bullet.png"))
	{
		std::cout << "Error loading texture (image)" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setColor(sf::Color::Red);
	
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
	//std::cout << "Bullet Created" << std::endl;
}


Bullet::~Bullet()
{
	//std::cout << "Bullet deconstuctor called" << std::endl;
}

void Bullet::handleEvents()
{
	if(checkCollision()) Alive = false;
	sprite.move(sf::Vector2f(velocity.x * charMove, velocity.y * charMove));
}

std::string Bullet::type()
{
	return "Bullet";
}
