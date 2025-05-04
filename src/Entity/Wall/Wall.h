#pragma once
#include "../Player/Player.h"
#include "../Entity.h"

class Wall 
{
public:
	//When making a wall Make sure the Y pos is the bottom of the wall no the top 
	// Then when chosing the height make the height how high you want the wall to extend up.
	Wall(int x, int y, int height);

private:
	int xPos;
	int  yPos;
	sf::RectangleShape hitBox;
};

