#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <iostream>

class Bullet : public Entity
{

public:

	Bullet(int _facing, Map*);
	~Bullet();
	void handleEvents() override;
	std::string type() override;
};

