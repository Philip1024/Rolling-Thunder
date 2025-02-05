#include "Player.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
Player::Player()
{
	texture.loadFromFile("res/SpriteSheets/Albatross.png");
	sprite.emplace(texture);
	//since sprite is in optional class it is treated as a pointer
	sprite->setPosition(sf::Vector2f(100, 120));
	sf::Vector2i position(230, 58);
	sf::Vector2i size(30, 60);
	xPos = 230;
	yPos = 58;
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
	sprite->setScale({0.8,0.8});
}


Player::~Player()
{




}


//updates sprite frames for walking right animation
void Player::updateRight()
{
	//changes pos in sprite sheet 
	if (xPos == 380)
		xPos = 230;
	else
		xPos += 30;
	sf::Vector2i position(xPos, yPos);
	sf::Vector2i size(30, 60);
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
	sprite->move({ 7.5,0 });//not exact yet
}


void Player::updateLeft()
{
	if (xPos > 170)
	{
		xPos = 170;
	}
	if (xPos == 50)
		xPos = 170;
	else
		xPos -= 30;
	sf::Vector2i position(xPos, yPos);
	sf::Vector2i size(30, 60);
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
	sprite->move({ -5.5,0 });//not exact yet

}