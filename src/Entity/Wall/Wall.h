#pragma once
#include "../Player/Player.h"
#include "../Entity.h"

class Wall 
{
public:
	//When making a wall Make sure the Y pos is the bottom of the wall no the top 
	// Then when chosing the height make the height how high you want the wall to extend up.
	Wall(int x, int y, int height);
	~Wall();
	sf::FloatRect* getBox() { return hitBox; }
	//Wall must make a rectangle shape that cannot be entered. It will be checked at the same time as other collisions in Game
	//Need walls at (8.5,175) and (1720,175) for sure to start
private:
	int xPos;
	int  yPos;
	sf::FloatRect* hitBox;
};