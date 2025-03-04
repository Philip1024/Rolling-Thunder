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
	//void update() override;
	//this opens the door if the player interacts with it 
	void open();
	void update(char actionFlags);
	sf::Clock clock;
	bool opening = false;
	int doorCount = 0;

	//void collide(Entity* other) override;

private:
};

