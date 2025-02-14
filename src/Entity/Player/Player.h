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

	int animationFrame;
};

