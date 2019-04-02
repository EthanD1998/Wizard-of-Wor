#pragma once
#include "pch.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Garwor : public Enemy
{
public:
	Garwor(Map*, std::vector<Entity*> *, Entity*);
	~Garwor();
	std::string type() override;
};

