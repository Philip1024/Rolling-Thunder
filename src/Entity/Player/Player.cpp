#include "Player.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
#include<math.h>



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
	jumpFrame = 1;
	xMov = 0;
	yMov = 0;
	xPos = 0;
	yPos = 0;
	t = 0;
	velo = 10;
	g = 9.8;
	angle = 45 * PI / 180;
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

	if (jumpFrame > 1)
		jumpFrame = 0;
	if ((actionFlags & 0b00000001) && !activeJump) // moving right. 
	{
		sprite.setTextureRect(AnimationData::getSection("albatross_move_right")->nextFrame());
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
			t = 0;
			velo = 25;
			g = 9.8;
			angle = 75 * PI / 180;
		}
		t += 0.2;
		xMov = velo * cos(angle) * t - xPos;
		xPos = velo * cos(angle) * t;
		yMov = -0.5 * g * t * t + velo * sin(angle) * t-yPos;
		yPos = -0.5 * g * t * t + velo * sin(angle) * t;
		sprite.move({ xMov, -1*yMov });
		view->move({ xMov,0 });
		sprite.setTextureRect(AnimationData::getSection("albatross_standard_jump")->getFrame(0));
		for (int i = 0; i < ground.size(); i++)
		{
			if (sprite.getGlobalBounds().findIntersection(ground.at(i))&&t>1)
			{
				activeJump = false;
				sprite.setTextureRect(AnimationData::getSection("albatross_move_right")->getFrame(0));
				sprite.move({ 0,-7 });
				xMov = 0;
				yMov = 0;
				xPos = 0;
				yPos = 0;
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
	}
}