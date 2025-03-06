#include "Enemy.h"
#include "../Player/Player.h"
#include"../Bullet/Bullet.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos)
	: Entity(AnimationData::getTexture(AnimationData::ENEMY))
{
	sprite.setPosition(pos);

	animationMap[WALK_LEFT] = new AnimationData::SectionData(AnimationData::getSection("enemy_move_left"));
	animationMap[WALK_RIGHT] = new AnimationData::SectionData(AnimationData::getSection("enemy_move_right"));
	animationMap[IDLE_CROUCH] = new AnimationData::SectionData(AnimationData::getSection("enemy_idle_sneak"));
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
	}


}

void Enemy::update(char actionFlags)
{
	curMove = IDLE_CROUCH;

	sprite.setTexture(*AnimationData::getTexture(AnimationData::ENEMY));

	switch (curMove)
	{
	case WALK_LEFT:
		sprite.setTexture(*AnimationData::getTexture(AnimationData::ENEMY_FLIPPED));
		break;
	case WALK_RIGHT:
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
	sf::RectangleShape bounds;
	bounds.setSize(sprite.getGlobalBounds().size);
	bounds.setPosition(sprite.getGlobalBounds().position);
	bounds.setFillColor(sf::Color::Transparent);
	bounds.setOutlineColor(sf::Color::Green);
	bounds.setOutlineThickness(1);
	window->draw(bounds);
	lastMove = curMove;
	
	Entity::update(actionFlags);
#ifdef DEBUG
#endif
}