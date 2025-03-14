#include "Door.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"


Door::Door(int x,int y): Entity(AnimationData::getTexture(AnimationData::DOOR))
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
	doors.push_back(this);
	pause = 0;
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
//still need to add sound for this 
void Door::open()
{
	sprite.setTextureRect(doorOpen->nextFrame());
	if (!opening)
	{
		opening = true;
	}
	doorFrameCount++;
	if (doorFrameCount == 3)
	{
		doorFrameCount = 0;
		opening = false;
		doorOpened = true;
		pause = true;
	}
}


//this just  a reverse of the the door opening animation
//still need to add sound for this
bool Door::close()
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
		return true;
	}
	return false;
}


//This controls the door opening and closing
//Im trying to implemnent a way to hold the door closed 
//by holding the w key after entering the door
void Door::update(char actionFlags, std::vector<sf::FloatRect>* ground)
{
	if (clock.getElapsedTime().asSeconds() <= 0.06f)
		return;

	if ((opening)&&!doorOpened)
	{
		open();
	}
	else if (pause < 4)
	{
		pause++;
	}
	else if  (doorOpened||closing)
	{
		//if this is true the door animation is done
		close();
	}
	clock.restart();

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
	opening = newOpening;
}


void Door::setClosing(bool newClosing)
{
	closing = newClosing;
}

bool Door::getOpen()
{
	return opening||(pause<4);
}


bool Door::getClosing()
{
	return closing;
}