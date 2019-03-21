#include "pch.h"
#include "Entity.h"

/*
	Entity Parent Class
		Most of these functions are blank and meant to be overridden by children.	
*/

Entity::Entity() 
{
	radarShape = sf::RectangleShape(sf::Vector2f(26, 26));
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

void Entity::respawn()
{
	sprite.setPosition(startPos);
}

bool Entity::checkCollision() 
{
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
	if(!map) return false;

	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));

	for (int i = pos.x - 1; i < pos.x + 2; i++) {
		for (int j = pos.y - 1; j < pos.y + 2; j++) {
			for (int k = 0; k < 4; k++) {
				if (!(i >= 13 || j >= 7 || i < 0 || j < 0)) {
					if (sprite.getGlobalBounds().intersects(map->at(i).at(j).at(k).getGlobalBounds())) {
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
