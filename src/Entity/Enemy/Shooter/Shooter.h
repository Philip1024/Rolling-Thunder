#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include"../../Entity.h"

class Shooter : public Entity
{
	void collide(Entity* other);
};

