#include "pch.h"
#include "Player.h"

/*
	Player needs a reference to the map so it can check collision.	
*/

Player::Player(Map* _map = nullptr)
{
	charScale = 2;
	charMove = 2;
	
	//radar color
	color = sf::Color::White;
	
	map = _map;
	
	texture.loadFromFile("Sprites/Worrior.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(sf::Vector2f(715, 418));
}



Player::~Player()
{
	
}

std::string Player::type()
{
	return "Player";
}


void Player::handleEvents()
{
	keyInput();
}

void Player::keyInput()
{
	/*
		Has to be setup this way in order to remove stuttering.
	*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sprite.setScale(charScale, charScale);
		sprite.setRotation(0);
		sprite.move(sf::Vector2f(charMove * -1, 0));
		if (checkCollision()) sprite.move(sf::Vector2f(charMove, 0));
		facing = W;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sprite.setScale(sf::Vector2f(charScale, -1 * charScale));
		sprite.setRotation(180);
		sprite.move(sf::Vector2f(charMove, 0));
		if (checkCollision()) sprite.move(sf::Vector2f(-1 * charMove, 0));
		facing = E;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sprite.setRotation(90);
		sprite.move(sf::Vector2f(0, -1 * charMove));
		if (checkCollision()) sprite.move(sf::Vector2f(0, charMove));
		facing = N;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sprite.setRotation(270);
		sprite.move(sf::Vector2f(0, charMove));
		if (checkCollision()) sprite.move(sf::Vector2f(0, -1 * charMove));
		facing = S;
	}
	
}
