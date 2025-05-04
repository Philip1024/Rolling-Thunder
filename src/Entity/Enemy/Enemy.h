#pragma once
#include "../Entity.h"
#include "../Player/Player.h"


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
		PUNCH_RIGHT,
		PUNCH_LEFT
	};
	Enemy(sf::Vector2f pos);
	~Enemy();

	void collide(Entity* other);
	void update(char actionFlags);
	void update(Player* pl);
	bool getAlive();
private:
	Movement curMove, lastMove;
	int moveTicks;
	std::vector<sf::FloatRect>* vec = new std::vector<sf::FloatRect>;
	std::unordered_map<Movement, AnimationData::SectionData*> animationMap;
	int health = 0;
	bool dying;
	bool alive;
};
