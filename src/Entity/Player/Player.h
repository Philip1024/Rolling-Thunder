#pragma once
#include"../Entity.h"
#include<optional>
class Player:public Entity
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
};

