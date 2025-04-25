#pragma once
#include<optional>
#include "../../SpriteData/AnimationData.h"
#include "../Entity.h"
#include "../Door/Door.h"
#include "../Raill/Rail.h"//typo
#include<vector>
class Player : public Entity
{
public:
	enum Movement
	{
		MOVE_LEFT,
		MOVE_RIGHT,
		STAND_LEFT,
		STAND_RIGHT,
		JUMP_LEFT,
		JUMP_RIGHT,
		DOOR_IN,
		DOOR_OUT,
		JUMP_RAIL_RIGHT,
		CLIMB_RAIL_RIGHT,
		CLIMB_RAIL_LEFT,
		FALL_RIGHT,
		FALL_LEFT
	};
	Player();
	~Player();
	void collide(Entity* other,char ActionFlags) override;
	void update(char actionFlags) ;
	bool playerInDoor() { return inDoor; }
	void setPos(sf::Vector2f);
	int getFloor() { return floor; }
	//void getGround1(std::vector<sf::FloatRect>);
	//void getGround2(std::vector<sf::FloatRect>);
	//sf::Vector2f getPosition();
private:
	//keeps track of time between sprite updates
	sf::Clock clock;
	sf::Clock doorTime;
	sf::Clock shootTime;
	Movement curMove;
	std::unordered_map<Movement, AnimationData::SectionData*> animationMap;
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
	bool shooting;
	int shootingFrame; //keeps track of frame count for shootign animation
	int doorCount; //used to determine how door should open when collides with door
	AnimationData::SectionData* moveLeft, * moveRight,*jumpLeft, *jumpRight, *walkInDoor, * walkOutDoor,*shootRight, *shootLeft;
	bool jump(double angle, std::vector<sf::FloatRect>*);
	int floor;//meant to represent what floor the player is on
	int playerTicks;
	bool jumpingRail;
	int jumpingRailCount;
	sf::IntRect frameUpdate;
	std::vector<sf::FloatRect> ground1;
	std::vector<sf::FloatRect> ground2;
};

