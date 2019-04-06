#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(float f, sf::Vector2f size, bool l)
: sf::Texture()
{
	loops = l;
	frameTime = f;
	create(size.x,size.y);
}

AnimatedTexture::~AnimatedTexture()
{
	
}

void AnimatedTexture::updateTexture()
{
	if(clock.getElapsedTime().asSeconds() >= frameTime)
	{
		clock.restart();
		nextFrame();
	}
	
	update(frames.at(currentFrame)); //error happens here.
	//std::cout << "Updated texture\n";
}

void AnimatedTexture::nextFrame()
{
	if(currentFrame == frames.size() - 1)
	{
		if(!loops)
		{
			Alive = false;
		}
			
		currentFrame = 0;
	}
	else
	{
		currentFrame++;
	}
}

AnimatedTexture::AnimatedTexture()
: sf::Texture()
{
}

void AnimatedTexture::addImage(std::string s)
{
	sf::Image t = sf::Image();
	
	if(t.loadFromFile(s))
	{
		//std::cout << "Added frame [" << s << "]\n";
		frames.push_back(t);
	}
}


