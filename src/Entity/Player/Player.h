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
	void collide(Entity* other) override;
	void update(char actionFlags,std::vector<sf::FloatRect>*);
	//sf::Vector2f getPosition();
private:
	//keeps track of time between sprite updates
	sf::Clock clock;
	bool faceRight;
	bool activeJump, activeRightJump, activeLeftJump;//used to determine whether player is actively jumping
	int jumpFrame;
	float xMov, yMov,xPos,yPos;//used to keep track of movement of sprite in jumping animation
	const double PI = 3.14159235;
	double t;
	double velo;
	double g;
	double angle;

	AnimationData::SectionData* moveLeft, * moveRight;
	bool jump(double angle, std::vector<sf::FloatRect>*);
};

