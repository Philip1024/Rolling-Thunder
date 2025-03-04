#pragma once
#include "../Entity.h"

class Enemy : public Entity
{
public:
	enum Movement
	{
		WALK_LEFT,
		WALK_RIGHT,
		DIE_LEFT,
		DIE_RIGHT,
		MOUNT_LEFT,
		MOUNT_RIGHT,
		SHOOT_LEFT,
		SHOOT_RIGHT,
		DOOR_WALK_OUT,
		DOOR_WALK_IN,
		IDLE_LEFT,
		IDLE_RIGHT,
		IDLE_CROUCH,
	};
	Enemy(sf::Vector2f pos);
	~Enemy();

	void collide(Entity* other);
	void update(char actionFlags);
private:
	Movement curMove;
	std::unordered_map<Movement, AnimationData::SectionData*> animationMap;
};
