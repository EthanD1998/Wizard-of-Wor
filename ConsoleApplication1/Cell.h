#pragma once
#include "walls.h"
#include <vector>
class Cell : public sf::Drawable
{
public:
	Cell();
	~Cell();
	void set(bool[4], int,int);
	std::vector<walls> getWalls();
	bool hasWall();
	void addWall(walls);
	void deleteLastWall();
private:
	bool isWall[4];
	std::vector<walls> wall;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

