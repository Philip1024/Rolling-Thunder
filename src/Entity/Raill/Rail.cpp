#include "Rail.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"

Rail::Rail(int x, int y) : Entity(AnimationData::getTexture(AnimationData::RAIL))
{
	xPos = x;
	yPos = y;
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	sprite.setScale({ 0.23f,0.23f });
	sf::Vector2i position(0, 0);
	sf::Vector2i size(200, 200);
	sf::IntRect frame(position, size);
	sprite.setTextureRect(frame);
	rails.push_back(this);
	rail = new AnimationData::SectionData(AnimationData::getSection("Rail"));
	floor = 1;
}

//this changes the visibilty of the debug door
//
void Rail::changeOpacity(bool visible)
{
	if (visible)
	{
		sprite.setColor(sf::Color(255, 255, 255, 0));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
}


void Rail::update(char actionFlags)
{
	
}

void Rail::setPos(sf::Vector2f a)
{
	int x = a.x;
	int y = a.y;
	sprite.setPosition(sf::Vector2f(x, y));
}

float Rail::getFront()
{
	return (float)xPos;
}


float Rail::getBack()
{
	return (float)(xPos + 45);
}

