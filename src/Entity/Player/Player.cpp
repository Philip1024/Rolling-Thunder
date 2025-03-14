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
	activeRightJump = false;
	activeLeftJump = false;
	falling = false;
	shouldFall = true;
	enterDoor = false;
	doorOpen = true;
	jumpFrame = 1;
	xMov = 0;
	yMov = 0;
	xPos = 0;
	yPos = 0;
	t = 0;
	velo = 10;
	g = 9.8;
	angle = 45 * PI / 180;

	moveRight = new AnimationData::SectionData(AnimationData::getSection("albatross_move_right"));
	moveLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_move_left"));
	jumpLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_jump_left"));
	jumpRight = new AnimationData::SectionData(AnimationData::getSection("albatross_jump_right"));
	walkInDoor = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_in_door"));
}


Player::~Player()
{
	delete moveLeft;
	delete moveRight;
}


/*
action flags structure:
right most bit (00000001): move right
7th bit (00000010): move left
6th bit (00000100): jump
*/
void Player::update(char actionFlags, std::vector<sf::FloatRect>* ground)
{
	Entity::update(actionFlags);
	if (clock.getElapsedTime().asSeconds() <= 0.05f)
		return; // only update the animation past this point
	//meant to determine whether player is on ground, if not player should fall
	shouldFall = true;
	for (int i = 0; i < ground->size(); i++)
	{
		if (sprite.getGlobalBounds().findIntersection(ground->at(i)) || activeRightJump || activeJump || activeLeftJump)
		{
			shouldFall = false;
		}
	}
	if (shouldFall)
		falling = true;
	if (falling)
	{
		if (faceRight)
			sprite.setTextureRect(AnimationData::getSection("albatross_falling_right")->getFrame(0));
		else
			sprite.setTextureRect(AnimationData::getSection("albatross_falling_left")->getFrame(0));
		sprite.move({ 0,5 });
		view->move({ 0,5 });
		if (!shouldFall)
		{
			falling = false;
			if (faceRight)
				sprite.setTextureRect(moveRight->nextFrame());
			else
				sprite.setTextureRect(moveLeft->nextFrame());
		}
			
	}
	if ((actionFlags & 0b00000001) && !activeRightJump && !activeJump && !activeLeftJump&&!falling) // moving right. 
	{
		sprite.setTextureRect(moveRight->nextFrame());
		view->move({ 7.5,0 });

		sprite.move({ 7.5,0 });//not exact yet
		faceRight = true;

	}
	if ((actionFlags & 0b00000010) && !activeRightJump && !activeJump && !activeLeftJump && !falling) // moving left TODO: bound check on the left using view
	{
		sprite.setTextureRect(moveLeft->nextFrame());
		view->move({ -7.5,0 });

		sprite.move({ -7.5,0 });//not exact yet
		faceRight = false;
	}

	if (((actionFlags & 0b00000100)||activeJump) &&!activeRightJump && !activeLeftJump && !falling)//jump
	{
		//represents time
		if (!activeJump)
		{
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeJump = true;
			t = 0;
			velo = 30;
			g = 9.8;
			angle = 90 * PI / 180;
		}
		activeJump = jump(angle, ground);
	}

	//jump follows a parabolic path using parametric physics equations
	//this is the jumping while moving right animation
	if (((actionFlags & 0b00001000) || activeRightJump) && !activeJump && !activeLeftJump && !falling)//jump
	{
		//represents time
		if (!activeRightJump)
		{
			faceRight = true;
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeRightJump = true;
			t = 0;
			velo = 30;
			g = 9.8;
			angle = 75 * PI / 180;
		}
		activeRightJump = jump(angle, ground);
	}
	if (((actionFlags & 0b00010000) || activeLeftJump) && !activeJump && !activeRightJump && !falling)//jump
	{
		//represents time
		if (!activeLeftJump)
		{
			faceRight = false;
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeRightJump = true;
			t = 0;
			velo = 30;
			g = 9.8;
			angle = 105 * PI / 180;
		}
		activeRightJump = jump(angle, ground);
	}
	//std::cout << sprite.getPosition().x <<' '<< sprite.getPosition().y << std::endl;
	clock.restart();
}

//foor colliding, not functional for door collision yet
void Player::collide(Entity* other,char actionFlags)
{
	if (doorTime.getElapsedTime().asSeconds() <= 0.01f)
		return;

	Door* doorCast = dynamic_cast<Door*>(other);
	if (doorCast != nullptr && ((actionFlags & 0b10000000)||enterDoor))
	{
		//starts door opening and has player walk into door
		if ((doorCast->getOpen()||doorOpen)&&!enterDoor)
		{
			sprite.setTextureRect(walkInDoor->nextFrame());
			sprite.move({ 0,-1 }); //player animation
			doorOpen = false;;//causing issue
			doorCast->setOpening(true);
			enterDoor = true;
		}
		if (!doorCast->getOpen())
		{
			sprite.setColor(sf::Color(255, 255, 255, 0));
			//enterDoor = false;
		}
	}
	doorTime.restart();
}



bool Player::jump(double angle, std::vector<sf::FloatRect>* ground)
{
	t += 0.4;
	xMov = velo * cos(angle) * t - xPos;
	xPos = velo * cos(angle) * t;
	yMov = -0.5 * g * t * t + velo * sin(angle) * t - yPos;
	yPos = -0.5 * g * t * t + velo * sin(angle) * t;
	sprite.move({ xMov, -1 * yMov });
	view->move({ xMov, -1 * yMov });
	if(faceRight)
		sprite.setTextureRect(AnimationData::getSection("albatross_standard_right_jump")->getFrame(0));
	else
		sprite.setTextureRect(AnimationData::getSection("albatross_standard_left_jump")->getFrame(0));
	for (int i = 0; i < ground->size(); i++)
	{
		if (sprite.getGlobalBounds().findIntersection(ground->at(i)) && t > 1)
		{
			if (!faceRight)
				sprite.setTextureRect(moveLeft->nextFrame());
			else
				sprite.setTextureRect(moveRight->nextFrame());
			sprite.move({ 0,-7 });
			xMov = 0;
			yMov = 0;
			xPos = 0;
			yPos = 0;
			return false;
		}
	}
	return true;
}
