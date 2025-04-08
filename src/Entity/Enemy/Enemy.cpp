#include "Enemy.h"
#include "../Player/Player.h"
#include"../Bullet/Bullet.h"
#include <iostream>
#include <math.h>
typedef AnimationData::SectionData SectionData;


Enemy::Enemy(sf::Vector2f pos)
	: Entity(AnimationData::getTexture(AnimationData::ENEMY))
{
	sprite.setPosition(pos);

	animationMap[WALK_LEFT] = new SectionData(AnimationData::getSection("enemy_move_left"));
	animationMap[WALK_RIGHT] = new SectionData(AnimationData::getSection("enemy_move_right"));
	animationMap[IDLE_CROUCH] = new SectionData(AnimationData::getSection("enemy_idle_sneak"));
	animationMap[IDLE_RIGHT] = new SectionData(AnimationData::getSection("enemy_idle_right"));
	animationMap[IDLE_LEFT] = new SectionData(AnimationData::getSection("enemy_idle_left"));
	animationMap[SHOOT_RIGHT] = new SectionData(AnimationData::getSection("enemy_shoot_right"));
	animationMap[PUNCH_LEFT] = new SectionData(AnimationData::getSection("enemy_punch_left"));
	animationMap[PUNCH_RIGHT] = new SectionData(AnimationData::getSection("enemy_punch_right"));
}


Enemy::~Enemy()
{
	for (auto& pair : animationMap)
		delete pair.second;
}


void Enemy::collide(Entity* other)
{
	//if they collide set the player bounce bool to true
	//then set shooter bounce bool to true.
	Player* playerCast = dynamic_cast<Player*>(other);
	if (playerCast != nullptr)
	{
		//playerCast->update();
	}

	//take away health from the enemy and start bullet death animation
	Bullet* bulletCast = dynamic_cast<Bullet*>(other);
	if (bulletCast != nullptr)
	{
		//bulletCast->update();
		if (curMove == WALK_LEFT || curMove == IDLE_LEFT || curMove == MOUNT_LEFT || curMove == SHOOT_LEFT)
		{
			curMove = DIE_LEFT;
		}
		else
		{
			curMove = DIE_RIGHT;
		}
	}


}


void Enemy::update(char actionFlags)
{
	throw std::exception("dont call this");
}


void Enemy::update(sf::Vector2f playerPos)
{
	sprite.setScale(sf::Vector2f(0.9, 0.9));

	// when the animation ends
	//if the enemy is in the process of death skip this statement
	//
	/*if (moveTicks <= 0 || curMove != DIE_LEFT || curMove != DIE_RIGHT)
	{
		if (abs(playerPos.x - sprite.getPosition().x) > 150 || rand() % 100 < ) 
		{
			curMove = IDLE_CROUCH;
			moveTicks = 9*4;
		}
		//if the enemy is close to the player
		else if(abs(playerPos.x - sprite.getPosition().x) < 30)
		{
			if (playerPos.x < sprite.getPosition().x)
				curMove = PUNCH_LEFT;
			else
				curMove = PUNCH_RIGHT;
		}
		//this determines where to walk
		else
		{

			if (playerPos.x < sprite.getPosition().x)
				curMove = WALK_LEFT;
			else
				curMove = WALK_RIGHT;
		}

	}
	moveTicks--;*/

	sprite.setTexture(*AnimationData::getTexture(AnimationData::ENEMY));

	switch (curMove)
	{
	case WALK_LEFT:
		sprite.move(sf::Vector2f(-1, 0));
		break;
	case WALK_RIGHT:
		sprite.move(sf::Vector2f(1, 0));
		break;
	case DIE_LEFT:
		break;
	case DIE_RIGHT:
		break;
	case MOUNT_LEFT:
		break;
	case MOUNT_RIGHT:
		break;
	case SHOOT_LEFT:
		break;
	case SHOOT_RIGHT:

		break;
	case DOOR_WALK_OUT:
		break;
	case DOOR_WALK_IN:
		break;
	case IDLE_LEFT:
		break;
	case IDLE_RIGHT:
		break;
	case IDLE_CROUCH:
		break;
	}
	if (getCurrentTick() % 4 == 0)
		sprite.setTextureRect(animationMap[curMove]->nextFrame());
	lastMove = curMove;

	Entity::update(0b0, vec);
#ifndef NDEBUG
	sf::RectangleShape bounds;
	bounds.setSize(sprite.getGlobalBounds().size);
	bounds.setPosition(sprite.getGlobalBounds().position);
	bounds.setFillColor(sf::Color::Transparent);
	bounds.setOutlineColor(sf::Color::Green);
	bounds.setOutlineThickness(1);
	window->draw(bounds);
#endif
}
