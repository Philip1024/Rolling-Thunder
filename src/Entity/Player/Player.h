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
		CLIMB_OFF_RAIL_RIGHT,
		CLIMB_OFF_RAIL_LEFT,
		FALL_RIGHT,
		FALL_LEFT
	};
	Player();
	~Player();
	void collide(Entity* other,char ActionFlags) override;
	void update(char actionFlags) ;
	/// <summary>
	/// returns when player is going through the door animation
	/// </summary>
	/// <returns>true if in door, false if not</returns>
	bool playerInDoor() { return inDoor; }
	/// <summary>
	/// sets positions of player
	/// </summary>
	/// <param name=""></param>
	void setPos(sf::Vector2f);
	int getFloor() { return floor; }
	/// <summary>
	/// gives players direction whether facing right of left
	/// </summary>
	/// <returns>returns true if player is right and false if player is facing left</returns>
	bool getDirection(){ return faceRight; }
private:
	//keeps track of time between sprite updates
	sf::Clock clock;
	sf::Clock doorTime;
	sf::Clock shootTime;
	sf::Clock invincibilityTime;
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
	bool droppingDown;//used to tell when player is dropping down to bottom floor
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
	int jumpingRailCount;//keeps track of frame count realitive to ticks(time 3) for jumping onto a rail
	bool jumpingOffRail;
	int jumpingOffRailCount;//keeps track of frame count realitive to ticks(time 3) for jumping off a rail
	bool dropping;//meant to represent when player makes big drop and viewport needs to move with jumps and fall
	bool invincibility;
	sf::FloatRect centerGroundCollision;
	std::vector<sf::FloatRect> ground1;
	std::vector<sf::FloatRect> ground2;
};

