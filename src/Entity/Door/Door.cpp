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
	doorOpen = new AnimationData::SectionData(AnimationData::getSection("door_open"));
	doorClose = new AnimationData::SectionData(AnimationData::getSection("door_close"));
	sprite.setTextureRect(AnimationData::getSection("door_open")->getFrame(0));
	
}

Door::~Door()
{
	delete doorOpen;
	delete doorClose;
}


//This opens the door for when the enmeyy leaves the room
//still need to add sound for this 
void Door::open()
{
	sprite.setTextureRect(doorOpen->nextFrame());
	if (!opening)
	{
		opening = true;
	}
	doorFrameCount++;
	if (doorFrameCount == 4)
	{
		doorFrameCount = 0;
		opening = false;
		doorOpened = true;
	}
}

//this just  a reverse of the the door opening animation
//still need to add sound for this
void Door::close()
{
	sprite.setTextureRect(doorClose->nextFrame());
	if (!closing)
	{
		closing = true;
	}
	doorFrameCount++;
	if (doorFrameCount == 4)
	{
		doorFrameCount = 0;
		closing = false;
		doorOpened = false;
	}
}

//This controls the door opening and closing
void Door::update(char actionFlags)
{
	
	if (clock.getElapsedTime().asSeconds() <= 0.13f)
		return;

	if ((actionFlags & 0b100000000 || opening)&&!doorOpened)
	{
		open();
	}

	if (doorOpened)
	{
		close();
	}
	clock.restart();
}
