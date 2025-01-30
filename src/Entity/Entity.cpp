#include "Entity.h"


Entity::Entity()
{
	entities.push_back(this);
}

void Entity::collide(Entity* other)
{
}
