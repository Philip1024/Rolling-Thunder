#pragma once
#include <vector>


class Entity
{
public:
	Entity();
	static std::vector<Entity*>& getEntities() { return entities; }
	virtual void collide(Entity* other) = 0;
private:
	static std::vector<Entity*> entities;
};