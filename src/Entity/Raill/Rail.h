#pragma once
#include"../Entity.h"
class Rail : public Entity
{
public:
	Rail(int x, int y);
	~Rail();

	void update(char actionFlags);
	void changeOpacity(bool visible);
	void setPos(sf::Vector2f a);
	float getFront();
	float getBack();
private:
	int xPos, yPos;
	AnimationData::SectionData* rail;
};

