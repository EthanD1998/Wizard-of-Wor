#pragma once
#include "pch.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"
#include <iostream>
class Worluk : public Enemy
{
public:
	Worluk(Map*, std::vector<Entity*> *, Entity*);
	~Worluk();

	std::string type() override;
};

