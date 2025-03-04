#include "Enemy.h"
#include "../Player/Player.h"
#include"../Bullet/Bullet.h"


Enemy::Enemy(sf::Vector2f pos)
	: Entity(AnimationData::getTexture(AnimationData::ENEMY))
{
	sprite.setPosition(pos);
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
	if (getCurrentTick() % 5 == 0)
	sprite.setTextureRect(AnimationData::getSection("enemy_move_left")->nextFrame());

	Entity::update(actionFlags);
}
