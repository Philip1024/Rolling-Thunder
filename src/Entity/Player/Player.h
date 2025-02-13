#pragma once
#include<optional>
#include "../Entity.h"
#include "../Door/Door.h"

class Player:public Entity
{
public:
	Player();
	~Player();
	int xPos, yPos; //represents position on sprite sheet
	//updates player sprite based on input
	void update();
	//updates player sprite so it does jumping to rail animation
private:
	bool faceRight;
	void collide(Entity* other) override;
};

