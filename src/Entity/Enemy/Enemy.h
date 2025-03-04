#pragma once
#include "../Entity.h"

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f pos);

	void collide(Entity* other);
	void update(char actionFlags);
};
