#include "pch.h"
#include "Map.h"
#include <iostream>

//please add comments

Map::Map()
{
	bool temp[4] = { false,false,false,false };

	cellMap.resize(13);
	for (int i = 0; i < 13; i++)
		cellMap.at(i).resize(7);

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cellMap.at(i).at(j).set(temp, i, j, sf::Color::Blue);
		}
	}
}

std::vector<int>* Map::getProperties()
{
	return &levelProperties;
}

int Map::getProperty(int t)
{
	return levelProperties.at(t);
}

Map::Map(std::string fileName)
{
	std::ifstream file("Levels/" + fileName);
	std::string value;

	sf::Color colors[4] = {sf::Color::Transparent, sf::Color::Blue, sf::Color::Red, sf::Color::Green};

	int intTemp = 0;
	bool temp[4];

	cellMap.resize(13);
	for (int i = 0; i < 13; i++)
		cellMap.at(i).resize(7);

	while (file.good())
	{
		for(int i=0; i < 4; i++)
		{
			getline(file, value, ',');
			levelProperties.push_back(std::atoi(value.c_str()));
		}
		
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					getline(file, value, ',');
					if (value.find("1") != std::string::npos)
					{
						intTemp++;
						temp[k] = true;
					}
					else
						temp[k] = false;
				}
				cellMap.at(i).at(j).set(temp, i, j, colors[levelProperties.at(3)]);
			}
		}
	}
	
	std::cout << cellMap.size() << std::endl;
}

Map::~Map()
{
}

Cell* Map::getCell(int x, int y)
{
	Cell *cellPtr = &cellMap.at(x).at(y);
	return cellPtr;
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			target.draw(cellMap.at(i).at(j), states);
		}
	}
}



