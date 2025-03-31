#pragma once
#include<optional>
#include "../../SpriteData/AnimationData.h"
#include "../Entity.h"
#include "../Door/Door.h"
#include<vector>
class Player : public Entity
{
public:
	Player();
	~Player();
	sf::Clock doorTime;
	void collide(Entity* other,char ActionFlags) override;
	void update(char actionFlags,std::vector<sf::FloatRect>*);
	void setPos(sf::Vector2f);
	//sf::Vector2f getPosition();
private:
	//keeps track of time between sprite updates
	sf::Clock clock;
	bool faceRight;
	bool activeJump, activeRightJump, activeLeftJump;//used to determine whether player is actively jumping
	bool falling;//used to determine if player is falling
	bool shouldFall;//used to determine if falling animation should occur
	bool enterDoor;//used to determine if player is entering door
	bool inDoor;//used to determine if player-door interaction is taking place
	bool exitDoor;
	bool exitOnce;//used to make sure door is only exited once
	int jumpFrame;
	float xGlobal, yGlobal;
	float xMov, yMov,xPos,yPos;//used to keep track of movement of sprite in jumping animation
	const double PI = 3.14159235;
	double t;
	double velo;
	double g;
	double angle;
	float xSize, ySize, xPosition, yPosition;//used to detect collisions
	int doorCount; //used to determine how door should open when collides with door
	AnimationData::SectionData* moveLeft, * moveRight,*jumpLeft, *jumpRight, *walkInDoor, * walkOutDoor;
	bool jump(double angle, std::vector<sf::FloatRect>*);
};

