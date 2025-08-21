#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include"../Entity.h"
class Bullet : public Entity
{

public:
	void collide(Entity* other, char actionFlags);
	sf::Vector2f getPos() { return sf::Vector2f(xPos, yPos); }
	bool team;
	void update(char actionFlags);
	bool direction;
	void setUsed(bool isUsed) { used = isUsed; }
	bool getUsed() { return used; }
	bool getInUse(){return inUse;}
	Bullet(bool bTeam, bool bDirection,float x, float y);
	AnimationData::SectionData* bulletRight, * bulletLeft;
private:
	float xPos, yPos;
	bool fired,used,inUse;
	sf::Clock pause;
};

