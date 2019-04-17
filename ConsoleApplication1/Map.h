#pragma once
#include "Cell.h"
#include <fstream>
#include <SFML/Graphics.hpp>



class Map : public sf::Drawable
{
public:
	Map();
	Map(std::string);
	~Map();
	Cell* getCell(int, int);
	std::vector<std::vector<Cell>> cellMap;
protected:
	
	//please add comments
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};