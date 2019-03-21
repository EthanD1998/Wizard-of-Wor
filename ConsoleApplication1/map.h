#pragma once
#include "Cell.h"
#include <fstream>
#include <SFML/Graphics.hpp>
class map : public sf::Drawable
{
public:
	map();
	map(std::string);
	~map();
	Cell* getCell(int, int);
	
private:
	std::vector<std::vector<Cell>> cellMap;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

