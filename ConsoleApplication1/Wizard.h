#pragma once
#include "Enemy.h"
class Wizard : public Enemy
{
public:
	Wizard(Map*, std::vector<Entity*> *, Entity*);
	~Wizard();

	std::string type() override;
};

