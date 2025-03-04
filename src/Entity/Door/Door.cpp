#include "Door.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"


Door::Door(int x,int y)
	: Entity(AnimationData::getTexture(AnimationData::DOOR))
{
	xPos = 215;
	yPos = 0;
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	sprite.setScale({ 0.8f,0.8f });
	sf::Vector2i position(215, 0);
	sf::Vector2i size(50, 60);
	sf::IntRect frame(position, size);
	sprite.setTextureRect(frame);
}


//The door will open 
//AMKE THE DOOR CHANGE POS AFTER THE FRAME IS SWITHCED. THEN RESET
//THE POS TO THE ORGIONAL DOOR POS
void Door::open()
{
	sprite.setTextureRect(AnimationData::getSection("door_open")->nextFrame());
}

void Door::update(char actionFlags)
{
	if (clock.getElapsedTime().asSeconds() <= 0.25f)
		return;
	if (actionFlags & 0b100000000 || opening)
	{
		if (!opening)
		{
			opening = true;
		}
		open();
		doorCount++;
		if (doorCount == 3)
		{
			doorCount = 0;
			opening = false;
			sprite.setColor(sf::Color::Black);
		}

	}
	clock.restart();
}
