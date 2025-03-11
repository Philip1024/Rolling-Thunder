#include "Rail.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"

Rail::Rail(int x, int y) : Entity(AnimationData::getTexture(AnimationData::RAIL))
{
	xPos = x;
	yPos = y;

}

