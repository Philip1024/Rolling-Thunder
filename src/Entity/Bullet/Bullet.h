#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include"../Entity.h"
class Bullet : public Entity
{
	void collide(Entity* other);
};

