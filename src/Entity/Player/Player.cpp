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
	sf::IntRect frame(position, size);
	sprite->setTextureRect(frame);
	sprite->setScale({0.8,0.8});
	faceRight = true;
	animationFrame = 5;
}


Player::~Player()
{

}


/*
action flags structure:
right most bit (00000001): move right
7th bit (00000010): move left
*/
void Player::update(char actionFlags)
{
	if (animationFrame > 5)
		animationFrame = 0;
	if (animationFrame < 0)
		animationFrame = 5;
	if (actionFlags & 0b00000001)
	{
		animationFrame = 0;
		sprite->setTextureRect(AnimationData::getSection("albatross_move_right")->getFrame(animationFrame++));
		sprite->move({ 7.5,0 });//not exact yet
		faceRight = true;

	}
	if (actionFlags & 0b00000010)
	{
		animationFrame = 4;
		sprite->setTextureRect(AnimationData::getSection("albatross_move_left")->getFrame(animationFrame--));
		sprite->move({ -7.5,0 });//not exact yet
		faceRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
	{
		animationFrame = 0;
		sprite->setTextureRect(AnimationData::getSection("albatross_standard_jump")->getFrame(animationFrame));

	}
}


void Player::collide(Entity* other)
{
	Door* doorCast = dynamic_cast<Door*>(other);

	if (doorCast != nullptr)
	{
		//doorCast->open();
		std::cout << "Works" << std::endl;
	}
}