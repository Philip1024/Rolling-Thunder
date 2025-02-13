#pragma once
#include"../Entity.h"


class Door : public Entity

{
public:
	Door(int x, int y);
	~Door();
	//represents position on sprite sheet
    //updates player sprite based on input
	int xPos, yPos;
	int animationFrame = 0;
	//This is used for opening  the door wwwww
	void update() override;


	//void collide(Entity* other) override;

private:
};

