#include "Entity.h"

Entity::Entity()
{
	//std::cout << "Entity Created" << std::endl;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));
	sf::RectangleShape s(sf::Vector2f(23,23));
	s.setFillColor(color);
	s.setPosition(sf::Vector2f((pos.x * 23) + 275, (pos.y * 23) + 410));
	target.draw(s);
}

Entity::~Entity()
{
	
}

void Entity::handleEvents()
{
	//std::cout << "Handled Events on entity" << std::endl;
}




bool Entity::checkCollision()
{
	if(!map) return false;
	
	sf::Vector2f pos(round((sprite.getPosition().x - 60) / 60), round((sprite.getPosition().y - 60) / 60));


	for (int i = pos.x - 1; i < pos.x + 2; i++)
	{
		for (int j = pos.y - 1; j < pos.y + 2; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (!(i >= 13 || j >= 7 || i < 0 || j < 0))
				{
					if (sprite.getGlobalBounds().intersects(map->at(i).at(j).at(k).getGlobalBounds()))
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
