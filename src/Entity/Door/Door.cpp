#include "Door.h"
#include"../Entity.h"
#include "../Player/Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"
#include"../Enemy/Enemy.h"

Door::Door(int x,int y): Entity(AnimationData::getTexture(AnimationData::DOOR))
{
	xPos = x;
	yPos = y; 
	closed = true;
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	sprite.setScale({ 0.8f,0.8f });
	sf::Vector2i position(215, 0);
	sf::Vector2i size(50, 60);
	sf::IntRect frame(position, size);
	sprite.setTextureRect(frame);
	doorOpen = new AnimationData::SectionData(AnimationData::getSection("door_open"));
	doorClose = new AnimationData::SectionData(AnimationData::getSection("door_close"));
	sprite.setTextureRect(AnimationData::getSection("door_open")->getFrame(0));
	doors.push_back(this);
	pause = 0;
	stop = false;
	opening = false;
	startOpen = false;
	closing = false;
	opened = false;
}


Door::~Door()
{
	delete doorOpen;
	delete doorClose;
}


void Door::setPos(sf::Vector2f a)
{
	int x = a.x;
	int y = a.y;
	sprite.setPosition(sf::Vector2f(x, y));
}


//This opens the door for when the enmeyy leaves the room
//still need to add sound for this, not using
void Door::open()
{
	//sprite.setTextureRect(doorOpen->nextFrame());
	sprite.setTextureRect(AnimationData::getSection("door_open")->getFrame(doorFrameCount));
	if (!opening)
	{
		opening = true;
	}
	doorFrameCount++;
	if (doorFrameCount == 4)
	{

		opening = false;
		doorOpened = true;
		pause = true;
	}
}


//this just  a reverse of the the door opening animation
//still need to add sound for this,not using
bool Door::close()
{
	//sprite.setTextureRect(doorClose->nextFrame());
	if (!closing)
	{
		closing = true;
		doorFrameCount = 3;
		pause = 0;
	}
	sprite.setTextureRect(AnimationData::getSection("door_close")->getFrame(doorFrameCount));
	doorFrameCount--;
	if (doorFrameCount == -1)
	{
		pause = 0;
		doorFrameCount = 0;
		closing = false;
		doorOpened = false;
		return true;
	}
	return false;
}


//This controls the door opening and closing
//Im trying to implemnent a way to hold the door closed 
//by holding the w key after entering the door
void Door::update(char actionFlags, float x, float y)
{
	int playerDistance = abs(x - sprite.getPosition().x);

	if (clock.getElapsedTime().asSeconds() >= 6 && enemySpawnCount < 6)
	{
		if (playerDistance < 50)
		{
			new Enemy(sf::Vector2f(float(sprite.getPosition().x), float(107)));
			enemySpawnCount++;
		}
	}

	if (clock.getElapsedTime().asSeconds() <= 0.06f)
		return;

	if (startOpen)
	{
		if (doorFrameCount < 4 && !opened)
		{
			sprite.setTextureRect(AnimationData::getSection("door_close")->getFrame(doorFrameCount));
			doorFrameCount++;
			opening = true;
		}
		else if (pause<2)
		{
			opening = false;
			opened = true;
			pause++;
			stop = true;
		}
		else
		{
			closing = true;
			doorFrameCount--;
			sprite.setTextureRect(AnimationData::getSection("door_close")->getFrame(doorFrameCount));
			if (doorFrameCount == 0)
			{
				startOpen = false;
				opened = false;
				pause = 0;
				stop = false;
				closing = false;
			}
			stop = false;
		}
	}
	clock.restart();
	Entity::update(0b0);
}


//this changes the visibilty of the debug door
//
void Door::changeOpacity(bool visible)
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


void Door::setOpening(bool newOpening)
{
	startOpen = newOpening;
	opening = newOpening;
}


void Door::setClosing(bool newClosing)
{
	closing = newClosing;
}

bool Door::getOpen()
{
	return opening;
}


bool Door::getStop()
{
	return stop;
}


bool Door::getClosing()
{
	return closing;
}


bool Door::isClosed()
{
	return closed;


}