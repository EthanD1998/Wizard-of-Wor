#include "pch.h"
#include "Player.h"

/*
	Player needs a reference to the map so it can check collision.	
*/

Player::Player(Map* _map = nullptr)
{
	charScale = 2;
	charMove = 2;
	
	color = sf::Color::White;
	
	startPos = sf::Vector2f(715, 418);

	lives = 4;

	map = _map;
	
	texture.loadFromFile("Sprites/Worrior.png");

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(startPos);

	for (int i = 0; i < 3; i++)
	{
		sf::Sprite p = sf::Sprite();
		p.setPosition(sf::Vector2f(780, 250 + (i * 60)));
		p.setScale(sf::Vector2f(charScale, charScale));
		p.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
		p.setTexture(texture);
		lifeDisplay.push_back(p);
	}

}

Player::~Player()
{
	
}

void Player::draw(sf::RenderWindow* target)
{
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));
	radarShape.setFillColor(color);
	radarShape.setPosition(sf::Vector2f((pos.x * 26) + 282 - 26, (pos.y * 26) + 410));

	target->draw(sprite);
	target->draw(radarShape);

	for (int i = 0; i < lifeDisplay.size(); i++)
	{
		target->draw(lifeDisplay.at(i));
	}
}

std::string Player::type()
{
	return "Player";
}

void Player::respawn()
{
	sprite.setPosition(startPos);
	lifeDisplay.pop_back();
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
