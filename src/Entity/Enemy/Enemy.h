#pragma once
#include "../Entity.h"

class Enemy : public Entity
{
public:
	Enemy();

	void collide(Entity* other);
	void update(char actionFlags);
};
