#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include"../Entity.h"
class Bullet : public Entity
{

public:

private:
	void collide(Entity* other);
};

