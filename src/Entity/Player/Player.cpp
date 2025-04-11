#include "Player.h"
#include"../Entity.h"
#include"../Bullet/Bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <math.h>



Player::Player()
	: Entity(AnimationData::getTexture(AnimationData::ALBATROSS))
{
	sprite.setPosition(sf::Vector2f(100, 120));
	sf::Vector2i position(230, 58);
	sf::Vector2i size(30, 60); 
	xPosition = 230;
	yPosition = 58;
	xSize = 30;
	ySize = 60;
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
	inDoor = false;
	exitDoor = false;
	exitOnce = false;
	jumpFrame = 1;
	//for jumps
	xMov = 0;
	yMov = 0;
	xPos = 0;
	yPos = 0;
	t = 0;
	velo = 10;
	g = 9.8;
	angle = 45 * PI / 180;
	shooting = false;
	moveRight = new AnimationData::SectionData(AnimationData::getSection("albatross_move_right"));
	moveLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_move_left"));
	jumpLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_jump_left"));
	jumpRight = new AnimationData::SectionData(AnimationData::getSection("albatross_jump_right"));
	walkInDoor = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_in_door"));
	walkOutDoor = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_out_door"));
	shootRight = new AnimationData::SectionData(AnimationData::getSection("albatross_shooting_right"));
	shootLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_shooting_left"));
	floor = 0;
	jumpingRail = false;
}


Player::~Player()
{
	delete moveLeft;
	delete moveRight;
	delete jumpLeft;
	delete jumpRight;
	delete walkInDoor;
	delete walkOutDoor;
}


/*
action flags structure:
right most bit (00000001): move right
7th bit (00000010): move left
6th bit (00000100): jump
*/

void Player::update(char actionFlags, std::vector<sf::FloatRect>* ground)
{
	Entity::update(actionFlags,ground);
	if (clock.getElapsedTime().asSeconds() <= 0.05)
		return; // only update the animation past this point
	//meant to determine whether player is on ground, if not player should fall
	//test
	shouldFall = true;
	for (int i = 0; i < ground->size(); i++)
	{
		//if intersects with ground or in any of the other unique animations don't fall
		if (sprite.getGlobalBounds().findIntersection(ground->at(0)) != std::nullopt || activeRightJump || activeJump || activeLeftJump || inDoor || shooting||jumpingRail)
			shouldFall = false;
	}

	if (shouldFall)
		falling = true;

	//falling animation
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
			sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
		}
			
	}

	if ((actionFlags & 0b00000001) && !activeRightJump && !activeJump && !activeLeftJump&&!falling&&!inDoor && !shooting) // moving right. 
	{
		sprite.setTextureRect(moveRight->nextFrame());
		view->move({ 7.5,0 });

		sprite.move({ 7.5,0 });//not exact yet
		faceRight = true;

	}

	if ((actionFlags & 0b00000010) && !activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting) // moving left TODO: bound check on the left using view
	{
		sprite.setTextureRect(moveLeft->nextFrame());
		view->move({ -7.5,0 });

		sprite.move({ -7.5,0 });//not exact yet
		faceRight = false;
	}

	if (((actionFlags & 0b00000100)||activeJump) &&!activeRightJump && !activeLeftJump && !falling && !inDoor && !shooting)//jump
	{
		//represents time
		if (!activeJump)
		{
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeJump = true;
			t = 0;
			velo = 30;
			g = 13;
			angle = 90 * PI / 180;
		}
		activeJump = jump(angle, ground);
	}

	//jump follows a parabolic path using parametric physics equations
	//this is the jumping while moving right animation
	if (((actionFlags & 0b00001000) || activeRightJump) && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting)//jump
	{
		//represents time
		if (!activeRightJump)
		{
			faceRight = true;
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeRightJump = true;
			t = 0;
			velo = 30;
			g = 13;
			angle = 75 * PI / 180;
		}
		activeRightJump = jump(angle, ground);
	}

	if (((actionFlags & 0b00010000) || activeLeftJump) && !activeJump && !activeRightJump && !falling && !inDoor&&!shooting)//jump
	{
		//represents time
		if (!activeLeftJump)
		{
			faceRight = false;
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeRightJump = true;
			t = 0;
			velo = 30;
			g = 13;
			angle = 105 * PI / 180;
		}
		activeRightJump = jump(angle, ground);
	}

	if ((actionFlags & 0b00100000||shooting) && !activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor)
	{
		if (shootTime.getElapsedTime().asSeconds() <= 0.1f)
			return;
		shooting = true;
		if (shootingFrame == 3)
		{
			shooting = false;
			shootingFrame = 0;
			if (faceRight)
				sprite.setTextureRect(moveRight->nextFrame());
			else
				sprite.setTextureRect(moveLeft->nextFrame());
			sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
		}
		else
		{
			shootingFrame++;
			if (faceRight)
			{
				sprite.setTextureRect(shootRight->nextFrame());
				if (shootingFrame == 2)
				{
					new Bullet(true, true, sprite.getPosition().x+35, sprite.getPosition().y-12);
				}
			}
			else
			{
				sprite.setTextureRect(shootLeft->nextFrame());
				if (shootingFrame == 2)
				{
					new Bullet(true, false, sprite.getPosition().x -25, sprite.getPosition().y -13);//still need to fix
				}
			}
		}
		shootTime.restart();

	}

	
	sf::RectangleShape bounds;
	bounds.setSize(sprite.getGlobalBounds().size);
	bounds.setPosition(sprite.getGlobalBounds().position);
	bounds.setFillColor(sf::Color::Transparent);
	bounds.setOutlineColor(sf::Color::Green);
	bounds.setOutlineThickness(1);
	window->draw(bounds);
	
	//std::cout << sprite.getPosition().x <<' '<< sprite.getPosition().y << std::endl;
	clock.restart();
}

//foor colliding, not functional for door collision yet
void Player::collide(Entity* other,char actionFlags)
{
	if (doorTime.getElapsedTime().asSeconds() <= 0.06f)
		return;

	Door* doorCast = dynamic_cast<Door*>(other);
	Rail* railCast = dynamic_cast<Rail*>(other);
	if ((railCast != nullptr && (actionFlags & 0b01000000)||jumpingRail) && !activeRightJump && !activeJump && !activeLeftJump && !falling&&!inDoor)
	{
		if (!jumpingRail)
		{
			if (faceRight)
			{
				sprite.setTextureRect((AnimationData::getSection("albatross_jumping_to_rail_right")->getFrame(0)));
				jumpingRail = true;
			}
		}
		else
		{
			sprite.setTextureRect((AnimationData::getSection("albatross_jumping_to_rail_right")->getFrame(1)));
			sprite.move({ 0,-2 });
		}
	}
	if (doorCast != nullptr && ((actionFlags & 0b10000000)||inDoor) && !activeRightJump && !activeJump && !activeLeftJump && !falling)
	{
		//starts door opening and has player walk into door one frame
		if (!enterDoor&&!inDoor)
		{
			inDoor = true;
			doorCast->setOpening(true);
			sprite.setTextureRect(walkInDoor->nextFrame());
			sprite.move({ 0,-1 });
			enterDoor = true;
		}
		//while door is opening player walks in door
		if (!doorCast->getClosing()&&enterDoor)
		{
			sprite.setTextureRect(walkInDoor->nextFrame());
			sprite.move({ 0,-1 });//player animation
		}
		//when door is closing player becomes invisible
		if (doorCast->getClosing()&&enterDoor)
		{
			sprite.setColor(sf::Color(255, 255, 255, 0));
			enterDoor = false;
		}
		//once key is released player can exit door
		if (!(actionFlags & 0b10000000))
		{
			exitDoor = true;
		}
		if (!enterDoor && exitDoor&&!doorCast->getClosing())
		{
			//starts door opening animation
			if (!exitOnce)
			{
				doorCast->setOpening(true);
				exitOnce = true;
			}
			//after door is opened player becomes visible and can exit door
			if (!doorCast->getOpen())
			{
				sprite.setTextureRect(walkOutDoor->nextFrame());
				sprite.move({ 0,4 });
				sprite.setColor(sf::Color(255, 255, 255, 255));
			}
			//after player has exited door and door isn't doing anything reset to walking position
			if(!doorCast->getClosing()&&!doorCast->getStop()&& !doorCast->getOpen())
			{
				if (!faceRight)
					sprite.setTextureRect(moveLeft->nextFrame());
				else
					sprite.setTextureRect(moveRight->nextFrame());
				sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
				//std::cout << "works" << std::endl;;
				inDoor = false;
				exitDoor = false;
				exitOnce = false;
			}
		}
		doorTime.restart();
	}
}



bool Player::jump(double angle, std::vector<sf::FloatRect>* ground)
{
	t += 0.4;
	//parabolic equation for jump, pos keeps track of position while Mov uses pos to track how much movement is required each frame
	xMov = velo * cos(angle) * t - xPos;
	xPos = velo * cos(angle) * t;
	yMov = -0.5 * g * t * t + velo * sin(angle) * t - yPos;
	yPos = -0.5 * g * t * t + velo * sin(angle) * t;
	sprite.move({ xMov, -1 * yMov });
	view->move({ xMov, 0});
	if(faceRight)
		sprite.setTextureRect(AnimationData::getSection("albatross_standard_right_jump")->getFrame(0));
	else
		sprite.setTextureRect(AnimationData::getSection("albatross_standard_left_jump")->getFrame(0));
	for (int i = 0; i < ground->size(); i++)
	{
		if (sprite.getGlobalBounds().findIntersection(ground->at(i)) != std::nullopt)
		{
			if (!faceRight)
				sprite.setTextureRect(moveLeft->nextFrame());
			else
				sprite.setTextureRect(moveRight->nextFrame());
			sprite.move({ 0,(120-sprite.getGlobalBounds().position.y) });
			view->move({ 0,(120 - sprite.getGlobalBounds().position.y) });
			xMov = 0;
			yMov = 0;
			xPos = 0;
			yPos = 0;
			return false;
		}
	}
	return true;
}

void Player::setPos(sf::Vector2f a)
{
	int x = a.x;
	int y = a.y;
	sprite.setPosition(sf::Vector2f(x, y));
}

