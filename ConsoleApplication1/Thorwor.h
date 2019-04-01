#pragma once
#include "pch.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Thorwor : public Enemy
{
public:
	Thorwor(Map*, std::vector<Entity*> *);
	~Thorwor();

	std::string type() override;
};

