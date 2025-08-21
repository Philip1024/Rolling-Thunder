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
	inUse = true;
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

/// <summary>
/// deals with animations for when bullet collides with enemy
/// </summary>
/// <param name="other">entity colliding with</param>
/// <param name="actionFlags">user input</param>
void Bullet::collide(Entity* other, char actionFlags)
{
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	if (enemy != nullptr)
	{
		enemy->collide(this);
	}
	
}


/// <summary>
/// updates bullet animation
/// </summary>
/// <param name="actionFlags">user input</param>
void Bullet::update(char actionFlags)
{
	Entity::update(actionFlags);//draws bullet
	if (used)
	{
		if (pause.getElapsedTime().asSeconds() <= 0.1f)
		{
			if (direction)
				sprite.setTextureRect(AnimationData::getSection("bullet_right")->getFrame(2));
			else
				sprite.setTextureRect(AnimationData::getSection("bullet_left")->getFrame(2));
		}
		else
		{
			inUse = false;
		}
	}
	else
	{
		if (!fired)
		{
			if (direction)
				sprite.setTextureRect(AnimationData::getSection("bullet_right")->getFrame(1));
			else
				sprite.setTextureRect(AnimationData::getSection("bullet_left")->getFrame(1));
			fired = true;
		}
		if (direction)
			sprite.move({ 5,0 });
		else
			sprite.move({ -5,0 });
	}
}

