#pragma once
#include"../Entity.h"
class Rail : public Entity
{
public:
	Rail(int x, int y,int rail);
	~Rail();
	void changeOpacity(bool visible);
	void setPos(sf::Vector2f a);
private:
	int xPos, yPos;
	AnimationData::SectionData* rail;
};

