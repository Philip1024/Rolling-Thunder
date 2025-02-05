#include "Door.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
Door::Door()
{
	texture.loadFromFile("res/SpriteSheets/Door.png");
	sprite.emplace(texture);
	sprite->setPosition(sf::Vector2f(200, 67));
	sf::Vector2i position(200, 58);
	sf::Vector2i size(30, 60);
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
}


void Door::open()
{
	//
}