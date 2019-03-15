#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

typedef std::vector<std::vector<std::vector<sf::RectangleShape>>> Map;

class Entity : public sf::Drawable
{
public:
	sf::Vector2f velocity;
	sf::Sprite sprite;	
	Map* map = nullptr;
	std::vector<Entity*>* entities;
	sf::Color color = sf::Color::Transparent;

	
	enum directions { N, S, E, W };
	int charScale, charMove;
	bool Alive = true;
	int facing = 0;
	
		
	Entity();
	~Entity();
	virtual bool checkCollision();
	virtual void handleEvents();
	virtual std::string type();
protected:
	sf::Texture texture;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

