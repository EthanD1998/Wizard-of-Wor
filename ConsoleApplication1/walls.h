#pragma once
#include <SFML/Graphics.hpp>
class Walls : public sf::Drawable
{
public:
	Walls();
	Walls(int, int, int);
	Walls(int, int, int, sf::Color);
	~Walls();
	void setWall(int, int, int);
	sf::RectangleShape getWall();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape Wall;
};

