#include "Enemy.h"
#include "../Player/Player.h"
#include"../Bullet/Bullet.h"
#include <iostream>
#include <math.h>
typedef AnimationData::SectionData SectionData;


Enemy::Enemy(sf::Vector2f pos,bool spawnInDoor)
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
	animationMap[HIT_RIGHT] = new SectionData(AnimationData::getSection("enemy_hit_right"));
	animationMap[HIT_LEFT] = new SectionData(AnimationData::getSection("enemy_hit_left"));
	animationMap[DIE_RIGHT] = new SectionData(AnimationData::getSection("enemy_dissolve_right"));
	animationMap[DIE_LEFT] = new SectionData(AnimationData::getSection("enemy_dissolve_left"));
	animationMap[WALK_OUT] = new SectionData(AnimationData::getSection("enemy_walk_out"));
	animationMap[FALL_LEFT] = new SectionData(AnimationData::getSection("enemy_fall_left"));
	animationMap[FALL_RIGHT] = new SectionData(AnimationData::getSection("enemy_fall_right"));
	enemys.push_back(this);
	dying = false;
	dyingCount = 0;
	alive = true;
	spawnDoor = spawnInDoor;
	spawnCount = 0;
	faceRight = true;
	ground.push_back(sf::FloatRect({ 20.f,166.f }, { 1700.f,5.f }));
	ground.push_back(sf::FloatRect({ 132.f,90.f }, { 441.f,5.f }));
	ground.push_back(sf::FloatRect({ 764.f,90.f }, { 375.f,5.f }));
	ground.push_back(sf::FloatRect({ 1333.f,90.f }, { 385.f,5.f }));
	ground.push_back(sf::FloatRect({ 1717.f,90.f }, { 46.f, 5.f }));
	ground.push_back(sf::FloatRect({ 1763.f,145.f }, { 48.f,5.f }));
	ground.push_back(sf::FloatRect({ 1811.f,203.f }, { 48.f, 5.f }));
	ground.push_back(sf::FloatRect({ 1859.f,273.f }, { 46.f,5.f }));
	ground.push_back(sf::FloatRect({ 1905.f,342.f }, { 51.f,5.f }));
	ground.push_back(sf::FloatRect({ 1952.f,415.f }, { 1650.f,5.f }));
}


Enemy::~Enemy()
{
	for (auto& pair : animationMap)
		delete pair.second;
}

/// <summary>
/// deals with collisions with other entities
/// </summary>
/// <param name="other">entity colliding with</param>
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
		if (!(bulletCast->getUsed()))
		{
			if (bulletCast->team)
			{
				dying = true;
				if (curMove == WALK_LEFT || curMove == IDLE_LEFT || curMove == MOUNT_LEFT || curMove == SHOOT_LEFT)
				{
					curMove = HIT_LEFT;
				}
				else
				{
					curMove = HIT_RIGHT;
				}
				bulletCast->setUsed(true);
			}
		}
	}
}

/// <summary>
/// don't call
/// </summary>
/// <param name="actionFlags"></param>
void Enemy::update(char actionFlags)
{
	throw std::exception("dont call this");
}
	

/// <summary>
/// updates and draws enemy
/// </summary>
/// <param name="player">pointer to player in game</param>
void Enemy::update(Player* player)
{
	sprite.setScale(sf::Vector2f(0.9, 0.9));

	// when the animation ends
	//if the enemy is in the process of death skip this statement
	//
	curMove = IDLE_RIGHT;
	shouldFall = true;
	int playerDistance = abs(player->getSprite().getPosition().x - sprite.getPosition().x);
	for (int i = 0; i < ground.size(); i++)
	{
		//std::cout << sprite.getGlobalBounds().position.x << sprite.getGlobalBounds().size.x << std::endl;
		if (sprite.getGlobalBounds().findIntersection(ground.at(i)) != std::nullopt||spawnDoor||dying)
		{
			shouldFall = false;
			if(!spawnDoor&&!dying)
				sprite.move({ 0,((ground.at(i).position.y-40) - sprite.getGlobalBounds().position.y)});
		}
	}

	if (shouldFall)
	{
		std::cout << "test";
		if (faceRight)
			curMove = FALL_RIGHT;
		else
			curMove = FALL_LEFT;
		/*
		for (int i = 0; i < ground.size(); i++)
		{
			if (sprite.getGlobalBounds().findIntersection(ground.at(i)) != std::nullopt||spawnDoor||dying)
			{
				shouldFall = false;
				if(!spawnDoor&&!dying)
					sprite.move({ 0,((ground.at(i).position.y - 46) - sprite.getGlobalBounds().position.y) });
			}
		}
		*/
	}
	if (spawnDoor)
	{
		curMove = WALK_OUT;
		spawnCount++;
		if(spawnCount > 25)
		{
			spawnDoor = false;
			curMove = IDLE_CROUCH;
		}
	}
	else if (dying)
	{
		if (dyingCount < 13)
		{
			//enemy has no direction enemy dies based of player direction because is the player is facing right
			//the enemy had to have died facing left
			if (curMove == WALK_OUT || curMove == IDLE_CROUCH)
			{
				if (player->getDirection())
					curMove = HIT_LEFT;
				else
					curMove = HIT_RIGHT;
			}
			if (curMove == WALK_LEFT || curMove == IDLE_LEFT || curMove == MOUNT_LEFT || curMove == SHOOT_LEFT)
			{
				curMove = HIT_LEFT;

			}
			else if(curMove == WALK_RIGHT || curMove == IDLE_RIGHT || curMove == MOUNT_RIGHT || curMove == SHOOT_RIGHT)
			{
				curMove = HIT_RIGHT;
			}
			dyingCount++;
		}
		else if (dyingCount == 14)
		{
			sprite.move({ 0,45 });
			dyingCount++;
		}
		else if (dyingCount < 40)
		{
			if (curMove == WALK_LEFT || curMove == IDLE_LEFT || curMove == MOUNT_LEFT || curMove == SHOOT_LEFT||curMove== HIT_LEFT)
			{
				curMove = DIE_LEFT;
			}
			else if(curMove == WALK_RIGHT || curMove == IDLE_RIGHT || curMove == MOUNT_RIGHT || curMove == SHOOT_RIGHT||curMove==HIT_RIGHT)
			{
				curMove = DIE_RIGHT;
			}
			dyingCount++;
		}
		else
		{
			alive = false;
			dying = false;
			dyingCount = 0;
		}
	}
	else if (moveTicks <= 0 && curMove != DIE_LEFT && curMove != DIE_RIGHT&&curMove != FALL_LEFT&&curMove != FALL_RIGHT)
	{
		if (player->playerInDoor() && playerDistance < 70)
		{
			int cycleTick = getCurrentTick() % 190;

			if (cycleTick < 60)
			{
				curMove = WALK_LEFT;
				faceRight = false;
			}
			else if (cycleTick < 95)
			{
				curMove = IDLE_RIGHT;//change to idle left later on when we have the animation
				faceRight = false;//because should be IDLE_LEFT we're just missing animation
			}
			else if (cycleTick < 150)
			{
				curMove = WALK_RIGHT;
				faceRight = true;
			}
			else
			{
				curMove = IDLE_RIGHT;
				faceRight = true;
			}
		}
		else if (playerDistance > 150 || rand() % 100 < 5)
		{
			curMove = IDLE_CROUCH;
			moveTicks = 9*4;
		}
		//if the enemy is close to the player
		else if(playerDistance < 30)
		{
			if (player->getSprite().getPosition().x < sprite.getPosition().x && playerDistance < 10)
				curMove = PUNCH_LEFT;
			else if (player->getSprite().getPosition().x > sprite.getPosition().x)
				curMove = PUNCH_RIGHT;
		}
		//this determines where to walk
		else
		{
			if (player->getSprite().getPosition().x < sprite.getPosition().x)
			{
				curMove = WALK_LEFT;
				faceRight = false;
			}
			else
			{
				curMove = WALK_RIGHT;
				faceRight = true;
			}
		}

	}
	moveTicks--;

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
	case HIT_LEFT:
		sprite.move(sf::Vector2f(1, 0));
		break;
	case HIT_RIGHT:
		sprite.move(sf::Vector2f(-1, 0));
		break;
	case WALK_OUT:
		sprite.move({ 0,0.24 });
		break;
	case FALL_LEFT:
		sprite.move({ 0,1 });
		break;
	case FALL_RIGHT:
		sprite.move({ 0,1 });
		break;
	}
	//std::cout << getCurrentTick() << std::endl;
	if (getCurrentTick() % 4 == 0)
		sprite.setTextureRect(animationMap[curMove]->nextFrame());
	lastMove = curMove;

	Entity::update(0b0);
#ifndef NDEBUG
	sf::RectangleShape bounds;
	bounds.setSize(sprite.getGlobalBounds().size);
	bounds.setPosition(sprite.getGlobalBounds().position);
	bounds.setFillColor(sf::Color::Transparent);
	bounds.setOutlineColor(sf::Color::Green);
	bounds.setOutlineThickness(1);
	//window->draw(bounds);
#endif
}


bool Enemy::getAlive()
{
	return alive;
}
