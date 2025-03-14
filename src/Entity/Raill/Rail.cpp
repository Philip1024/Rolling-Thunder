#include "Rail.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"

Rail::Rail(int x, int y, int raill) : Entity(AnimationData::getTexture(AnimationData::RAIL_LEFT))
{
	/*
	Entity(AnimationData::getTexture(AnimationData::RAIL_MIDDLE));
	Entity(AnimationData::getTexture(AnimationData::RAIL_RIGHT));
	xPos = x;
	yPos = y;
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	sprite.setScale({ 0.18f,0.18f });
	sf::Vector2i position(0, 0);
	sf::Vector2i size(100, 60);
	sf::IntRect frame(position, size);
	sprite.setTextureRect(frame);
	if (raill == 1)
	{
		rail = new AnimationData::SectionData(AnimationData::getSection("Rail_Left"));
		sprite.setTextureRect(AnimationData::getSection("Rail_left")->getFrame(0));
	}
	else if (raill == 2)
	{
		rail = new AnimationData::SectionData(AnimationData::getSection("Rail_Middle"));
		sprite.setTextureRect(AnimationData::getSection("Rail_Middle")->getFrame(0));
	}
	else if (raill == 3)
	{
		rail = new AnimationData::SectionData(AnimationData::getSection("Rail_Right"));
		sprite.setTextureRect(AnimationData::getSection("Rail_Right")->getFrame(0));
	}
	rails.push_back(this);
	*/
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


void Rail::setPos(sf::Vector2f a)
{
	int x = a.x;
	int y = a.y;
	sprite.setPosition(sf::Vector2f(x, y));
}

