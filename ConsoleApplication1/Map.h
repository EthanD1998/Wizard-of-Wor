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
	std::vector<int>* getProperties();
	int getProperty(int);
	
protected:
	std::vector<std::vector<Cell>> cellMap;
	std::vector<int> levelProperties;
	//please add comments
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

