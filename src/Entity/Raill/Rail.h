#pragma once
#include"../Entity.h"
class Rail : public Entity
{
public:
	Rail(int x, int y);
	~Rail();
private:
	int xPos, yPos;
};

