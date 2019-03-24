#include "pch.h"
#include "Player.h"

/*
	Player needs a reference to the map so it can check collision.	
*/

Player::Player(Map* _map = nullptr, std::vector<Entity*>* e = nullptr)
{
	entities = e;
	
	team = 0;
	
	killable = false;
	
	charScale = 2;
	charMove = 2;
	
	sprite.setRotation(90);
	
	color = sf::Color::White;
	
	startPos = sf::Vector2f(715, 418);

	lives = 4;

	level = _map;
	
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
	
	font.loadFromFile("Fonts/Adore.ttf");
		
	scoreText.setFont(font);
	scoreText.setString("000");
	scoreText.setCharacterSize(35);
	
	scoreText.setFillColor(sf::Color::Blue);

	sf::FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreText.setPosition(sf::Vector2f(720,500));
	

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
	
	target->draw(scoreText);
}

std::string Player::type()
{
	return "Player";
}

void Player::respawn()
{
	killable = false;
	sprite.setPosition(startPos);
	lifeDisplay.pop_back();
	level->getCell(11, 5)->deleteLastWall();
}

void Player::handleEvents()
{
	keyInput();
	
	int temp;
	temp = round(clock.getElapsedTime().asSeconds());
	if(temp > timeAlive)
	{
		timeAlive = temp;
	}
	
	scoreText.setString(std::to_string(score));
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
