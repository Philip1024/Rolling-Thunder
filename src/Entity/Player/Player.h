#pragma once
#include<SFML/Graphics.hpp>
#include"../Entity.h"
#include<optional>
class Player: public Entity
{
	Player();
	void collide(Entity* other) = 0;


};

