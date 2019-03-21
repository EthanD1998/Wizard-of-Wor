#pragma once
#include <SFML/Graphics.hpp>
class walls : public sf::Drawable
{
public:
	walls();
	walls(int, int, int);
	walls(int, int, int, sf::Color);
	~walls();
	void setWall(int, int, int);
	sf::RectangleShape getWall();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape wall;
};

