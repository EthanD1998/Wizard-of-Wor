#include "pch.h"
#include "Player.h"

/*
	Player needs a reference to the map so it can check collision.	
*/

Player::Player(Map* _map, std::vector<Entity*>* e, int playerLives, int playerScore, int p)
{
	playerType = p;
	entities = e;
	
	lives = playerLives;
	score = playerScore;
	
	team = p;
	
	killable = false;
	
	charScale = 2;
	charMove = .13;
	
	sprite.setRotation(90);
	
	color = sf::Color::White;
	
	
	startPos = sf::Vector2f(715 - (playerType * 600), 418);

	level = _map;
	
	texture.loadFromFile("Sprites/Worrior" + std::to_string(playerType) + ".png");
	
	animation = AnimatedTexture(.1f, sf::Vector2f(20,20), true);
	
	for(int i = 1; i < 3 + 1; i++)
	{
		animation.addImage("Sprites/Worrior" + std::to_string(playerType) + "/Worrior (" + std::to_string(i) + ").png");
	}
	
	sprite.setTexture(animation);
	sprite.setScale(sf::Vector2f(charScale, charScale));
	sprite.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
	sprite.setPosition(startPos);

	for (int i = 0; i < lives - 1; i++)
	{
		sf::Sprite p = sf::Sprite();
		p.setPosition(sf::Vector2f(780 - (playerType * 720), 250 + (i * 60)));
		p.setScale(sf::Vector2f(charScale, charScale));
		p.setOrigin(sprite.getLocalBounds().height / 2, sprite.getLocalBounds().width / 2);
		p.setTexture(texture);
		lifeDisplay.push_back(p);
	}
	
	font.loadFromFile("Fonts/Adore.ttf");
		
	scoreText.setFont(font);
	scoreText.setString("0000");
	scoreText.setCharacterSize(35);
	
	scoreText.setFillColor(sf::Color::Blue);

	sf::FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreText.setPosition(sf::Vector2f(720 - (playerType * 600),500));
	
	switch(playerType)
	{
		case 0:
			controls.push_back(sf::Keyboard::A);
			controls.push_back(sf::Keyboard::D);
			controls.push_back(sf::Keyboard::W);
			controls.push_back(sf::Keyboard::S);
			controls.push_back(sf::Keyboard::Space);
			break;
		case 1:
			controls.push_back(sf::Keyboard::Left);
			controls.push_back(sf::Keyboard::Right);
			controls.push_back(sf::Keyboard::Up);
			controls.push_back(sf::Keyboard::Down);
			controls.push_back(sf::Keyboard::M);
			break;
	}
	
	std::cout << "Created Player " << playerType << std::endl;
}

Player::~Player()
{
	
}

void Player::draw(sf::RenderWindow* target)
{
	sf::Vector2f pos = getPosition();
	radarShape.setFillColor(color);
	radarShape.setPosition(sf::Vector2f((pos.x * 26) + 282 - 26, (pos.y * 26) + 410));

	target->draw(sprite);
	target->draw(radarShape);
	target->draw(scoreText);
	
	for (int i = 0; i < lifeDisplay.size(); i++)
	{
		target->draw(lifeDisplay.at(i));
	}
	
}

std::string Player::type()
{
	return "Player" + std::to_string(playerType);
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
	
	animation.updateTexture();
	scoreText.setString(std::to_string(score));
}

void Player::keyInput()
{
	int t = clock.getElapsedTime().asMilliseconds();
	/*
		Has to be setup this way in order to remove stuttering.
	*/
	
	if (sf::Keyboard::isKeyPressed(controls.at(4)))
	{
		shoot();
	}
	if (sf::Keyboard::isKeyPressed(controls.at(0)))
	{
		sprite.setScale(charScale, charScale);
		sprite.setRotation(0);
		sprite.move(sf::Vector2f(charMove * -1 * t, 0));
		if (checkCollision()) sprite.move(sf::Vector2f(charMove * t, 0));
		facing = W;
	}
	if (sf::Keyboard::isKeyPressed(controls.at(1)))
	{
		sprite.setScale(sf::Vector2f(charScale, -1 * charScale));
		sprite.setRotation(180);
		sprite.move(sf::Vector2f(charMove * t, 0));
		if (checkCollision()) sprite.move(sf::Vector2f(-1 * charMove * t, 0));
		facing = E;
	}
	if (sf::Keyboard::isKeyPressed(controls.at(2)))
	{
		sprite.setRotation(90);
		sprite.move(sf::Vector2f(0, -1 * charMove * t));
		if (checkCollision()) sprite.move(sf::Vector2f(0, charMove * t));
		facing = N;
	}
	if (sf::Keyboard::isKeyPressed(controls.at(3)))
	{
		sprite.setRotation(270);
		sprite.move(sf::Vector2f(0, charMove * t));
		if (checkCollision()) sprite.move(sf::Vector2f(0, -1 * charMove * t));
		facing = S;
	}
	clock.restart().asSeconds();
}
