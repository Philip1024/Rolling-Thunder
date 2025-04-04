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
	sprite.setTextureRect(AnimationData::getSection("bullet_right")->getFrame(0));
	sprite.setScale({ 0.8f,0.8f });
	bullets.push_back(this);
	bulletLeft = new AnimationData::SectionData(AnimationData::getSection("bullet_left"));
	bulletRight = new AnimationData::SectionData(AnimationData::getSection("bullet_right"));
	fired = false;
	//true is left, false is right
	if(direction)
	{ 
		sprite.setTextureRect(AnimationData::getSection("bullet_right")->getFrame(0));
	}
	else
	{
		sprite.setTextureRect(AnimationData::getSection("bullet_left")->getFrame(0));
	}
}

void Bullet::collide(Entity* other, char actionFlags)
{
	
}


//if side is true then use left, else use right
//this will be called by player
void Bullet::update(char actionFlags, std::vector<sf::FloatRect>*)
{
	if (!fired&&pause.getElapsedTime().asSeconds()>=0.1f)
	{
		if (direction)
			sprite.setTextureRect(AnimationData::getSection("bullet_right")->getFrame(1));
		else
			sprite.setTextureRect(AnimationData::getSection("bullet_left")->getFrame(1));
		fired = true;
	}
	if(direction)
		sprite.move({ 5,0 });
	else 
		sprite.move({ -5,0 });
}

