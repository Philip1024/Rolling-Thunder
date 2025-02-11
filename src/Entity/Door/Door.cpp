#include "Door.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>


Door::Door(int x,int y)
{
	xPos = 215;
	yPos = 0;
	texture.loadFromFile("res/SpriteSheets/Door.png");
	sprite.emplace(texture);
	sprite->setPosition(sf::Vector2f(x, y));
	sprite->setScale({ 0.8,0.8 });
	sf::Vector2i position(215, 0);
	sf::Vector2i size(50, 60);
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
}


void Door::open()
{
	if (xPos >= 315)
		xPos = 215;
	else
		xPos += 43;
	sf::Vector2i position(xPos, yPos);
	sf::Vector2i size(50,60);
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
}