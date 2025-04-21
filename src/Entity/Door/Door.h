#pragma once
#include "../Entity.h"
#include "../Player/Player.h"


class Door : public Entity

{
public:
	Door(int x, int y);
	~Door();
	//represents position on sprite sheet
    //updates player sprite based on input
	int xPos, yPos;
	int animationFrame = 0;
	void update(char actionFlags);
	void update2(Player* pl);
	//this opens the door if the player interacts with it 
	void setPos(sf::Vector2f);
	void setOpening(bool);
	void setClosing(bool);
	bool getOpen();//returns when door is opening or open
	//retruns when door is open of closing
	bool getClosing();
	bool isClosed();
	bool getStop();
	void changeOpacity(bool visible);
	float getFront() { return (float) (xPos-5); }
	float getBack() { return (float) (xPos + 5); }
	//void collide(Entity* other) override;

private:
	AnimationData::SectionData* doorOpen, * doorClose;
	void open();
	bool close();
	sf::Clock clock;
	bool startOpen;
	bool opened;
	bool opening = false;
	bool closing = false;
	bool stop;
	bool closed;
	int pause;
	int doorFrameCount = 0;
	bool doorOpened = false;
	sf::RectangleShape door;
	int enemySpawnCount = 0
};

