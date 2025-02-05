#pragma once
#include"../Entity.h"


class Door:public Entity

{
public:
	Door();
	~Door();
	//represents position on sprite sheet
    //updates player sprite based on input
	int xPos, yPos;
	//this opens the door if the player interacts with it 
	void open();

private:
};

