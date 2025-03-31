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
	void update(char actionFlags, std::vector<sf::FloatRect>* ground);
	//this opens the door if the player interacts with it 
	void setPos(sf::Vector2f);
	void setOpening(bool);
	void setClosing(bool);
	bool getOpen();//returns when door is opening or open
	//retruns when door is open of closing
	bool getClosing();
	bool isClosed();
	void changeOpacity(bool visible);
	//void collide(Entity* other) override;

private:
	AnimationData::SectionData* doorOpen, * doorClose;
	void open();
	bool close();
	sf::Clock clock;
	bool opening = false;
	bool closing = false;
	bool stop;
	bool closed;
	int pause;
	int doorFrameCount = 0;
	bool doorOpened = false;
	sf::RectangleShape door;
};

