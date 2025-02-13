#include "Door.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include "../../SpriteData/AnimationData.h"


Door::Door(int x,int y)
{
	
	texture.loadFromFile("res/SpriteSheets/Door.png");
	sprite.emplace(texture);
	sprite->setPosition(sf::Vector2f(x, y));
	sprite->setScale({ 0.8,0.8 });
	sf::Vector2i position(215, 0);
	sf::Vector2i size(50, 60);
	sf::IntRect frame(position, size);
	sprite->setTextureRect(AnimationData::getSection("door_open")->getFrame(animationFrame));
}


//The door will open
void Door::update()
{
	if (animationFrame == 3)
		animationFrame = 0;
		
	sprite->setTextureRect(AnimationData::getSection("door_open")->getFrame(animationFrame++));

}
