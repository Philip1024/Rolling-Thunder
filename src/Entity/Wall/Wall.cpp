#include "Wall.h"

Wall::Wall(int x, int y, int height)
{
	xPos = x;
	yPos = y;
	hitBox = new sf::FloatRect({ (float)(xPos),(float)(yPos) }, { 1.f,(float)( - 1 * height)});
}


Wall::~Wall()
{
	delete hitBox;
}