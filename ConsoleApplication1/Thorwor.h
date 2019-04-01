#pragma once
#include "pch.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Thorwor : public Enemy
{
public:
	Thorwor(Map*, std::vector<Entity*> *, Entity*);
	~Thorwor();

	void columnOpacity() override;
	std::string type() override;
};
 
