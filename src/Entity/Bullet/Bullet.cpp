#include "Bullet.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include"../Enemy/Enemy.h"

Bullet::Bullet(bool bTeam,bool bDirection, float x, float y) : Entity(AnimationData::getTexture(AnimationData::BULLET))
{
	team = bTeam;//true means player, flase means enemy
	direction = bDirection;//true means right, false means left
	xPos = x;
	yPos = y;
	sprite.setPosition(sf::Vector2f((float)x, (float)y));
	sprite.setScale({ 0.23f,0.23f });
	sf::Vector2i position(0, 0);
	sf::Vector2i size(200, 200);
	sf::IntRect frame(position, size);
	sprite.setTextureRect(frame);
	bullets.push_back(this);
	bulletLeft = new AnimationData::SectionData(AnimationData::getSection("bulletLeft"));
	bulletRight = new AnimationData::SectionData(AnimationData::getSection("bulletRight"));
	fired = false;
	//true is left, false is right
	if(direction)
	{ 
		AnimationData::getSection("bulletLeft")->getFrame(0);
	}
	else
	{
		AnimationData::getSection("bulletRight")->getFrame(0);
	}
}

void Bullet::collide(Entity* other, char actionFlags)
{
	
}


//if side is true then use left, else use right
//this will be called by player
void Bullet::update(char actionFlags, std::vector<sf::FloatRect>*)
{
	if (!fired)
	{
		if (direction)
			bulletLeft->nextFrame();
		else
			bulletRight->nextFrame();
		fired = true;
	}
	if(direction)
		sprite.move({ 1,0 });
	else 
		sprite.move({ -1,0 });
}

