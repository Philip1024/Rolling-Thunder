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
		HIT_LEFT,
		HIT_RIGHT,
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
		PUNCH_LEFT,
		WALK_OUT
	};
	Enemy(sf::Vector2f pos,bool spawnInDoor);
	~Enemy();

	void collide(Entity* other);
	void update(char actionFlags);
	void update(Player* pl);
	/// <summary>
	/// gives whether enemy is alive
	/// </summary>
	/// <returns>true if enemy is alive, false if enemy is dead</returns>
	bool getAlive();
	/// <summary>
	/// gives whether enemy is spawning
	/// </summary>
	/// <returns>true if enemy is spawning, false if enemy isn't spawning</returns>
	bool getSpawn() { return spawnDoor; }
	/// <summary>
	/// gives whether enemy is in dying animation
	/// </summary>
	/// <returns>true if enemy is dying, false if enemy isn't dying</returns>
	bool getDying() { return dying; }
private:
	Movement curMove, lastMove;
	int moveTicks;
	std::vector<sf::FloatRect>* vec = new std::vector<sf::FloatRect>;
	std::unordered_map<Movement, AnimationData::SectionData*> animationMap;
	int health = 0;
	bool dying;
	int dyingCount;
	bool alive;
	bool spawnDoor;// tells if enemy spawns out of a door
	int spawnCount;
};
