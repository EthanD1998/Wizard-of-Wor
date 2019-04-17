#pragma once
#include "Walls.h"
#include <vector>
class Cell : public sf::Drawable
{
public:
	Cell();
	~Cell();
	void set(bool[4], int,int,sf::Color);
	std::vector<Walls> getWalls();
	bool hasWall();
	void addWall(Walls);
	void deleteLastWall();
	void color(sf::Color);
	void image(const sf::Texture*);
private:
	bool isWall[4];
	std::vector<Walls> Wall;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

