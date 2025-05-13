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


/// <summary>
/// This makes the rail change from visible to invisible
/// </summary>
/// <param name="visible">this determines what to make the rail</param>
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
/// <summary>
/// This sets the pos of the rail
/// </summary>
/// <param name="a"> a is the pos vector</param>
void Rail::setPos(sf::Vector2f a)
{
	int x = a.x;
	int y = a.y;
	sprite.setPosition(sf::Vector2f(x, y));
}

/// <summary>
/// This gets the front of the rails pos
/// </summary>
/// <returns></returns>
float Rail::getFront()
{
	return (float)xPos;
}

/// <summary>
/// This returns the back of the rails pos
/// </summary>
/// <returns></returns>
float Rail::getBack()
{
	return (float)(xPos + 45);
}

