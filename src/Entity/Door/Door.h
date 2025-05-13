#pragma once
#include "../Player/Player.h"
#include "../Entity.h"



class Door : public Entity

{
public:
	Door(int x, int y);
	~Door();
	//represents position on sprite sheet
	//updates player sprite based on input
	int xPos, yPos;
	int animationFrame = 0;
	void update(char actionFlags, float x, float y, bool*, sf::Clock*);
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
	float getFront() { return (float)(xPos - 5); }
	float getBack() { return (float)(xPos + 5); }
	//void collide(Entity* other) override;

private:
	AnimationData::SectionData* doorOpen, * doorClose;
	void open();
	bool close();
	sf::Clock clock;
	sf::Clock enemyClock;
	bool startOpen;
	bool opened;
	//for walking out
	bool topFloor;
	bool opening = false;
	bool closing = false;
	bool stop;
	int spawnCount = 0;
	bool closed;
	bool spawnOnce;//used to make sure only one enemy spawns when enemys are spawning from doors
	int pause;
	int doorFrameCount = 0;
	bool doorOpened = false;
	sf::RectangleShape door;
	int enemySpawnCount = 0;
	//this is true if an enemy has recently spawned
	bool enemySpawned;
};

