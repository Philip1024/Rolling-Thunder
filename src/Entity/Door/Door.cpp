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
	spawnOnce = false;
	enemyClock.restart();
}


Door::~Door()
{
	delete doorOpen;
	delete doorClose;
}

/// <summary>
/// This sets the pos of the door
/// </summary>
/// <param name="a"></param>
void Door::setPos(sf::Vector2f a)
{
	int x = a.x;
	int y = a.y;
	sprite.setPosition(sf::Vector2f(x, y));
}


/// <summary>
/// door opening animation not currently in use
/// </summary>
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


/// <summary>
/// door closing animation, not currently in use
/// </summary>
/// <returns></returns>
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


/// <summary>
/// updates the door and draws, spawns enemies and deals with door animations when player enters a door
/// </summary>
/// <param name="actionFlags">user input</param>
/// <param name="x">player x-cordinate</param>
/// <param name="y">player y-cordinate</param>
/// <param name="allowEnemyDoorSpawn">determines whether enemies can spawn</param>
/// <param name="enemySpawnClock">clock control cooldown for enemy spawning</param>
void Door::update(char actionFlags, float x, float y, bool* allowEnemyDoorSpawn, sf::Clock* enemySpawnClock)
{
	Entity::update(0b0);
	int playerDistanceX = abs(x - sprite.getPosition().x);
	int playerDistanceY = abs(y - sprite.getPosition().y);

	//change to check the Y coordinate of player position
	if (((playerDistanceX* playerDistanceX) + (playerDistanceY* playerDistanceY) < 2500 && *allowEnemyDoorSpawn && doorFrameCount == 0)||enemySpawned)
	{
		enemySpawned = true;
		//door opens
		if (doorFrameCount < 4 && !opened)
		{
			spawnOnce = true;
			sprite.setTextureRect(AnimationData::getSection("door_close")->getFrame(doorFrameCount));
			doorFrameCount++;
			opening = true;
		}
		//door is open and enemy walks out
		else if (pause < 20)
		{
			//so only one enemy spawns
			if (spawnOnce)
			{
				new Enemy(sf::Vector2f(float(sprite.getPosition().x - 9), float(sprite.getPosition().y - 4)), true);
				spawnOnce = false;
			}
			opening = false;
			opened = true;
			pause++;
			stop = true;
		}
		//door closes
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
				enemySpawned = false;
				spawnOnce = true;
			}
			stop = false;
		}
		*allowEnemyDoorSpawn = false;
		enemySpawnClock->restart();
	}
	//update frames every 0.06 seconds
	if (clock.getElapsedTime().asSeconds() <= 0.06f)
		return;

	if (startOpen&&!enemySpawned)
	{
		//door opens
		if (doorFrameCount < 4 && !opened)
		{
			sprite.setTextureRect(AnimationData::getSection("door_close")->getFrame(doorFrameCount));
			doorFrameCount++;
			opening = true;
		}
		//door stays open 
		else if (pause<2)
		{
			opening = false;
			opened = true;
			pause++;
			stop = true;
		}
		//door closes
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
}


/// <summary>
/// This makes the door visible or invisible
/// </summary>
/// <param name="visible"></param>
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