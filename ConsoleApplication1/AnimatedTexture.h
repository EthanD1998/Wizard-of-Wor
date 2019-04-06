#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimatedTexture : public sf::Texture
{
	public:
		AnimatedTexture(float, sf::Vector2f, bool);
		AnimatedTexture();
		~AnimatedTexture();
		
		bool Alive = true;
		
		void updateTexture();
		void addImage(std::string);
	
	private:
		void nextFrame();
		
		
		bool loops;
		std::vector<sf::Image> frames;
		unsigned int currentFrame = 0;
		float frameTime;
		sf::Clock clock;
	
};
