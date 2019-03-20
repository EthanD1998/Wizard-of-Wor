#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Entity.h"

class Bullet : public Entity
{

public:

	Bullet(int _facing, Map*);
	~Bullet();
	void handleEvents() override;
	std::string type() override;
};

