#pragma once
#include "../Player/Player.h"
#include "../Entity.h"

class Wall : public Entity
{
public:

	Wall();

private:
	int xPos;
	int  yPos;
	sf::RectangleShape hitBox;
};

