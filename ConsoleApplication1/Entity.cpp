#include "pch.h"
#include "Entity.h"
#include "Bullet.h"


/*
	Entity Parent Class
		Most of these functions are blank and meant to be overridden by children.	
*/

Entity::Entity() 
{
	radarShape = sf::RectangleShape(sf::Vector2f(26, 26));
	team = 1; // entity team;
}

sf::Vector2f Entity::getPosition()
{
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));
	return pos;
}

void Entity::draw(sf::RenderWindow* target) 
{
	/*
		sf::Drawable's draw function.
			Allows us to do target.draw(Entity);
	*/
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));
	radarShape.setFillColor(color);
	radarShape.setPosition(sf::Vector2f((pos.x * 26) + 282 - 26, (pos.y * 26) + 410));

	target->draw(sprite);
	target->draw(radarShape);
}

Entity::~Entity() 
{

}

void Entity::handleEvents() 
{
}

void Entity::shoot()
{
	if (!bulletExists())
	{
		Bullet* b = new Bullet(level, facing, team, entities);
		b->sprite.setPosition(sprite.getPosition());
		entities->push_back(b);
	}
}

bool Entity::bulletExists()
{
	for (int i = 0; i < entities->size(); i++)
	{
		if (entities->at(i)->type().find("Bullet" + std::to_string(team)) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

void Entity::respawn()
{
	sprite.setPosition(startPos);
}

	/*
		This function is long and complicated.
		Essentially, each Entity will find it's position in the grid.
			Then, it will check collision with each wall one block away from it.
			
			
			+---+---+---+  <--- X represents the Entity, and it checks all the walls in the boxes directly surrounding it.
			|   |   |   |
			+---+---+---+
			|   | X |   |
			+---+---+---+
			|   |   |   |
			+---+---+---+
			
			This is way more effecient than checking all the walls.
			
			0/10 would not reccomend trying to make it more effecient.
	*/
	
bool Entity::checkCollision()
{
	if(!level) return false;
	
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));


	for (int i = pos.x - 1; i < pos.x + 2; i++)
	{
		for (int j = pos.y - 1; j < pos.y + 2; j++)
		{
			if (!(i >= 13 || j >= 7 || i < 0 || j < 0))
			{
				for (int k = 0; k < level->getCell(i,j)->getWalls().size(); k++)
				{
		
					if (sprite.getGlobalBounds().intersects(level->getCell(i,j)->getWalls().at(k).getWall().getGlobalBounds()))
					{
						return true;
					}
				}

			}
		}
	}
	return false;
}

std::string Entity::type() 
{
	return "Entity";
}
