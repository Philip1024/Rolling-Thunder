#include "Player.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>



Player::Player()
	: Entity(AnimationData::getTexture(AnimationData::ALBATROSS))
{
	sprite.setPosition(sf::Vector2f(100, 120));
	sf::Vector2i position(230, 58);
	sf::Vector2i size(30, 60);
	sf::IntRect frame(position, size);
	sprite.setTextureRect(frame);
	sprite.setScale({0.8f,0.8f});
	faceRight = true;
	activeJump = false;
	animationFrame = 5;
	jumpFrame = 1;
	xMov = 0;
	yMov = 0;//pushes sprite down initally so sprite starts at floor
	xPos = 0;
	yPos = 0;
}


Player::~Player()
{

}


/*
action flags structure:
right most bit (00000001): move right
7th bit (00000010): move left
6th bit (00000100): jump
*/
void Player::update(char actionFlags, std::vector<sf::FloatRect> ground)
{
	Entity::update(actionFlags);

	if (clock.getElapsedTime().asSeconds() <= 0.05f)
		return; // only update the animation past this point

	if (animationFrame > 5)
		animationFrame = 0;
	if (animationFrame < 0)
		animationFrame = 5;
	if (jumpFrame > 1)
		jumpFrame = 0;
	if ((actionFlags & 0b00000001) && !activeJump) // moving right. 
	{
		sprite.setTextureRect(AnimationData::getSection("albatross_move_right")->getFrame(animationFrame++));
		view->move({ 7.5,0 });

		sprite.move({ 7.5,0 });//not exact yet
		faceRight = true;

	}
	if ((actionFlags & 0b00000010) && !activeJump) // moving left TODO: bound check on the left using view
	{
		sprite.setTextureRect(AnimationData::getSection("albatross_move_left")->nextFrame());
		view->move({ -7.5,0 });

		sprite.move({ -7.5,0 });//not exact yet
		faceRight = false;
	}
	//jump follows a parabolic path
	//not done yet
	if ((actionFlags & 0b00000100) || activeJump)//jump
	{
		//represents time
		if (!activeJump)
		{
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeJump = true;
		}
		double t = 0;
		double velo = 1;
		double g = 9.8;
		double angle = 45;
		//sprite.move({ 0,-5 });
		//view->move({ 1,0 });
		for (int i = 0; i < ground.size(); i++)
		{
			if (sprite.getGlobalBounds().findIntersection(ground.at(i)))
			{
				activeJump = false;
			}


		}
	}
	
	clock.restart();
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