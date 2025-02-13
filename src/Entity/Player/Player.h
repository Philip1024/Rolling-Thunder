#pragma once
#include<optional>
#include "../../SpriteData/AnimationData.h"
#include "../Entity.h"
#include "../Door/Door.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	int xPos, yPos; //represents position on sprite sheet
	//updates player sprite based on input
	void updateRight(float);
	void updateLeft(float);	
	//updates player sprite so it does jumping to rail animation
	void jumpToRail(float);
private:
	bool faceRight;

	int animationFrame;
	void collide(Entity* other) override;
};

