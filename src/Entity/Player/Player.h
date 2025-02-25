#pragma once
#include<optional>
#include "../../SpriteData/AnimationData.h"
#include "../Entity.h"
#include "../Door/Door.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	void collide(Entity* other) override;
	void update(char actionFlags) override;
private:
	//keeps track of time between sprite updates
	sf::Clock clock;
	bool faceRight;
	bool activeJump;//used to determine whether player is actively jumping
	bool heightJumped;
	int animationFrame, jumpFrame;
	float xMov, yMov,xPos,yPos;//used to keep track of movement of sprite in jumping animation
};

