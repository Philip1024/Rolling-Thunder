#include "Player.h"
#include"../Entity.h"
#include"../Bullet/Bullet.h"
#include"../Enemy/Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <math.h>
#include<vector>



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
	animationMap[MOVE_RIGHT] = new AnimationData::SectionData(AnimationData::getSection("albatross_move_right"));
	animationMap[MOVE_LEFT] = new AnimationData::SectionData(AnimationData::getSection("albatross_move_left"));
	animationMap[STAND_RIGHT] = new AnimationData::SectionData(AnimationData::getSection("albatross_stand_right"));
	animationMap[STAND_LEFT] = new AnimationData::SectionData(AnimationData::getSection("albatross_stand_left"));
	animationMap[JUMP_RIGHT] = new AnimationData::SectionData(AnimationData::getSection("albatross_standard_right_jump"));
	animationMap[JUMP_LEFT] = new AnimationData::SectionData(AnimationData::getSection("albatross_standard_left_jump"));
	animationMap[DOOR_IN] = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_in_door"));
	animationMap[DOOR_OUT] = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_out_door"));
	animationMap[CLIMB_RAIL_RIGHT] = new  AnimationData::SectionData(AnimationData::getSection("albatross_climbing_onto_rail_right"));
	animationMap[CLIMB_RAIL_LEFT] = new  AnimationData::SectionData(AnimationData::getSection("albatross_climbing_onto_rail_left"));
	animationMap[CLIMB_OFF_RAIL_RIGHT] = new  AnimationData::SectionData(AnimationData::getSection("albatross_climbing_off_rail_right"));
	animationMap[CLIMB_OFF_RAIL_LEFT] = new  AnimationData::SectionData(AnimationData::getSection("albatross_climbing_off_rail_left"));
	animationMap[FALL_RIGHT] = new AnimationData::SectionData(AnimationData::getSection("albatross_falling_right"));
	animationMap[FALL_LEFT] = new AnimationData::SectionData(AnimationData::getSection("albatross_falling_left"));
	playerTicks = 0;
	moveRight = new AnimationData::SectionData(AnimationData::getSection("albatross_move_right"));
	moveLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_move_left"));
	jumpLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_jump_left"));
	jumpRight = new AnimationData::SectionData(AnimationData::getSection("albatross_jump_right"));
	walkInDoor = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_in_door"));
	walkOutDoor = new  AnimationData::SectionData(AnimationData::getSection("albatross_walk_out_door"));
	shootRight = new AnimationData::SectionData(AnimationData::getSection("albatross_shooting_right"));
	shootLeft = new AnimationData::SectionData(AnimationData::getSection("albatross_shooting_left"));
	//shootleft start on wrong frame this sets it to right frame
	shootLeft->nextFrame();
	shootLeft->nextFrame();
	floor = 0;
	jumpingRail = false;
	jumpingRailCount = 0;
	jumpingOffRail = false;
	jumpingOffRailCount = 0;
	dropping = false;
	curMove = STAND_RIGHT;
	ground1.push_back(sf::FloatRect({ 20.f,166.f }, { 1700.f,5.f }));
	ground2.push_back(sf::FloatRect({ 132.f,84.f }, { 441.f,5.f }));
	ground2.push_back(sf::FloatRect({ 764.f,87.f }, { 375.f,5.f }));
	ground2.push_back(sf::FloatRect({ 1333.f,88.f }, { 385.f,5.f }));
	ground2.push_back(sf::FloatRect({ 1717.f,87.f }, { 46.f, 5.f }));
	ground2.push_back(sf::FloatRect({ 1763.f,145.f }, { 48.f,5.f }));
	ground2.push_back(sf::FloatRect({ 1811.f,203.f }, { 48.f, 5.f }));
	ground2.push_back(sf::FloatRect({ 1859.f,273.f }, { 46.f,5.f }));
	ground2.push_back(sf::FloatRect({ 1905.f,342.f }, { 51.f,5.f }));
	ground2.push_back(sf::FloatRect({ 1952.f,415.f }, { 1650.f,5.f }));
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

void Player::update(char actionFlags)
{
	Entity::update(actionFlags);//draws player
	 // only update the animation past this pointdddddddddd
	//meant to determine whether player is on ground, if not player should fall
	//test
	shouldFall = true;
	if (floor == 0)
	{
		for (int i = 0; i < ground1.size(); i++)
		{
			//if intersects with ground or in any of the other unique animations don't fall
			if (sprite.getGlobalBounds().findIntersection(ground1.at(i)) != std::nullopt || activeRightJump || activeJump || activeLeftJump || inDoor || shooting || jumpingRail || jumpingOffRail)
			{
				shouldFall = false;
				centerGroundCollision = ground1.at(i);
			}
				
		}
	}
	else
	{
		for (int i = 0; i < ground2.size(); i++)
		{
			//if intersects with ground or in any of the other unique animations don't fall
			if (sprite.getGlobalBounds().findIntersection(ground2.at(i)) != std::nullopt || activeRightJump || activeJump || activeLeftJump || inDoor || shooting || jumpingRail || jumpingOffRail)
			{
				shouldFall = false;
				centerGroundCollision = ground2.at(i);
				if (i >= 3 && i <= 7&& sprite.getGlobalBounds().findIntersection(ground2.at(i)) != std::nullopt)
					dropping = true;
				else
					dropping = false;
			}
		}
	}

	if (shouldFall)
		falling = true;

	//falling animation
	if (falling)
	{
		if (faceRight)
			curMove = FALL_RIGHT;
		else
			curMove = FALL_LEFT;
		if (floor == 1)
		{
			for (int i = 0; i < ground1.size(); i++)
			{
				//if intersects with ground or in any of the other unique animations don't fall
				if (sprite.getGlobalBounds().findIntersection(ground1.at(i)) != std::nullopt || activeRightJump || activeJump || activeLeftJump || inDoor || shooting || jumpingRail||jumpingOffRail)
				{
					falling = false;
					sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
					floor = 0;
				}
			}
		}
		sprite.move({ 0,5 });
		if(dropping)
			view->move({ 0,5 });
		if (!shouldFall)
		{
			std::cout << 0.75f * centerGroundCollision.position.y << std::endl;
			falling = false;
			if (faceRight)
				sprite.setTextureRect(moveRight->nextFrame());
			else
				sprite.setTextureRect(moveLeft->nextFrame());
			if(floor==0)
				sprite.move({ 0,((centerGroundCollision.position.y-43) - sprite.getGlobalBounds().position.y)});
			else
				sprite.move({ 0,((centerGroundCollision.position.y-43) - sprite.getGlobalBounds().position.y) });
		}
			
	}
	if (floor==1||jumpingOffRail)
	{
		if ((actionFlags == 0b01000010||jumpingOffRail) && !activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting && !jumpingRail)
		{
			if (!jumpingOffRail)
			{
				jumpingOffRail = true;
			}
			else if (jumpingOffRailCount < 10)
			{
				//this is done so player is drawn in front of the rail
				if (jumpingOffRailCount > 5)
					floor = 0;
				if (faceRight)
					curMove = CLIMB_OFF_RAIL_RIGHT;
				else
					curMove = CLIMB_OFF_RAIL_LEFT;
				jumpingOffRailCount++;
			}
			else
			{
				floor = 0;
				jumpingOffRail = false;
				jumpingOffRailCount = 0;

			}
		}
	}
	if ((actionFlags == 0b00000001) && !activeRightJump && !activeJump && !activeLeftJump&&!falling&&!inDoor && !shooting && !jumpingRail) // moving right. 
	{
		curMove = MOVE_RIGHT;
		faceRight = true;

	}

	if ((actionFlags == 0b00000010) && !activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting && !jumpingRail) // moving left TODO: bound check on the left using view
	{
		curMove = MOVE_LEFT;
		faceRight = false;
	}

	if (((actionFlags == 0b00000100)||activeJump) &&!activeRightJump && !activeLeftJump && !falling && !inDoor && !shooting && !jumpingRail)//jump
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
		if (floor == 0)
			activeJump = jump(angle, &ground1);
		else
			activeJump = jump(angle, &ground2);
	}

	//jump follows a parabolic path using parametric physics equations
	//this is the jumping while moving right animation
	if (((actionFlags == 0b00001000) || activeRightJump) && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting && !jumpingRail)//jump
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
		if (floor == 0)
			activeRightJump = jump(angle, &ground1);
		else
			activeRightJump = jump(angle, &ground2);
	}

	if (((actionFlags == 0b00010000) || activeLeftJump) && !activeJump && !activeRightJump && !falling && !inDoor&&!shooting && !jumpingRail)//jump
	{
		//represents time
		if (!activeLeftJump)
		{
			faceRight = false;
			sprite.move({ 0,7 });//when switchiong to jump animation player move up, this offsets that
			activeLeftJump = true;
			t = 0;
			velo = 30;
			g = 13;
			angle = 105 * PI / 180;
		}
		if (floor == 0)
			activeLeftJump = jump(angle, &ground1);
		else
			activeLeftJump = jump(angle, &ground2);
	}

	if ((actionFlags == 0b00100000||shooting) && !activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor && !jumpingRail)
	{
		if (shootTime.getElapsedTime().asSeconds() <= 0.1f)
			return;
		if (!shooting)
		{
			shooting = true;
			if(!faceRight)
				sprite.move({ -2.f,5.f });
			else
				sprite.move({ 2.f,5.f });
		}
		if (shootingFrame == 3)
		{
			shooting = false;
			if(!faceRight)
				sprite.move({ 2.f,-5.f });
			else
				sprite.move({ -2.f,-5.f });
			shootingFrame = 0;
			if (faceRight)
				sprite.setTextureRect(moveRight->nextFrame());
			else
				sprite.setTextureRect(moveLeft->nextFrame());
			//sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
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
	switch (curMove)
	{
	case MOVE_RIGHT:
		view->move({ 3,0 });
		sprite.move({ 3,0 });
		break;
	case MOVE_LEFT:
		view->move({ -3,0 });
		sprite.move({ -3,0 });
		break;

	}
	if (playerTicks % 3 == 0&&!shooting)
	{
		sprite.setTextureRect(animationMap[curMove]->nextFrame());

	}
	if (faceRight && !activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting &&!jumpingRail && !jumpingOffRail)
		curMove = STAND_RIGHT;
	if(!faceRight&&!activeRightJump && !activeJump && !activeLeftJump && !falling && !inDoor && !shooting && !jumpingRail && !jumpingOffRail)
		curMove = STAND_LEFT;
	playerTicks++;
	
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

/// <summary>
/// This method enacts all players actions when certain collisions happen
/// </summary>
/// <param name="other">The entity that it collides with.</param>
/// <param name="actionFlags">user input</param>
void Player::collide(Entity* other,char actionFlags)
{
	
	Enemy* enemyCast = dynamic_cast<Enemy*>(other);
	Door* doorCast = dynamic_cast<Door*>(other);
	Rail* railCast = dynamic_cast<Rail*>(other);
	if (enemyCast != nullptr)
	{
		//getspawn is called so player can't get hit right when enemy spawns from the door
		if (!enemyCast->getSpawn())
		{
			std::cout << "works" << std::endl;
		}
	}
	if ((railCast != nullptr && (actionFlags == 0b01000000)||jumpingRail&& railCast != nullptr) && !activeRightJump && !activeJump && !activeLeftJump && !falling&&!inDoor)
	{
		if (railCast->getFloor()-1==floor)
		{
			if (!jumpingRail)
			{
				if (faceRight)
				{
					sprite.setTextureRect((AnimationData::getSection("albatross_jumping_to_rail_right")->getFrame(0)));
					jumpingRail = true;
				}
				else
				{
					sprite.setTextureRect((AnimationData::getSection("albatross_jumping_to_rail_left")->getFrame(1)));
					jumpingRail = true;
				}
			}
			else
			{
				if (sprite.getPosition().y > 45)
				{
					if (faceRight)
					{
						sprite.setTextureRect((AnimationData::getSection("albatross_jumping_to_rail_right")->getFrame(1)));
						sprite.move({ 0,-2 });
					}
					else
					{
						sprite.setTextureRect((AnimationData::getSection("albatross_jumping_to_rail_left")->getFrame(0)));
						sprite.move({ 0,-2 });
					}
				}
				else
				{
					if (jumpingRail && jumpingRailCount < 10)
					{
						if (faceRight)
							curMove = CLIMB_RAIL_RIGHT;
						else
							curMove = CLIMB_RAIL_LEFT;
						jumpingRailCount++;
					}
					else
					{
						floor = 1;
						jumpingRail = false;
						jumpingRailCount = 0;
					}
				}

			}
		}
	}
	if (doorCast != nullptr && ((actionFlags == 0b01000001)||inDoor) && !activeRightJump && !activeJump && !activeLeftJump && !falling&&!jumpingRail)
	{
		//starts door opening and has player walk into door one frame
		if (!enterDoor&&!inDoor)
		{
			inDoor = true;
			doorCast->setOpening(true);
			curMove = DOOR_IN;
			sprite.move({ 0,-0.25 });
			enterDoor = true;
		}
		//while door is opening player walks in door
		if (!doorCast->getClosing()&&enterDoor)
		{
			curMove = DOOR_IN;
			sprite.move({ 0,-0.25 });//player animation
		}
		//when door is closing player becomes invisible
		if (doorCast->getClosing()&&enterDoor)
		{
			sprite.setColor(sf::Color(255, 255, 255, 0));
			enterDoor = false;
		}
		//once key is released player can exit door
		if (!(actionFlags == 0b01000001))
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
				curMove = DOOR_OUT;
				sprite.move({ 0,0.25 });
				sprite.setColor(sf::Color(255, 255, 255, 255));
			}
			//after player has exited door and door isn't doing anything reset to walking position
			if (floor == 0)
			{
				if (!doorCast->getClosing() && !doorCast->getStop() && !doorCast->getOpen() && sprite.getGlobalBounds().position.y > 120)
				{
					/*
					if (!faceRight)
						curMove = MOVE_LEFT;
					else
						curMove = MOVE_RIGHT;
						*/
					sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
					//std::cout << "works" << std::endl;;
					inDoor = false;
					exitDoor = false;
					exitOnce = false;
				}
			}
			else
			{
				if (!doorCast->getClosing() && !doorCast->getStop() && !doorCast->getOpen() && sprite.getGlobalBounds().position.y > 43)
				{
					/*
					if (!faceRight)
						curMove = MOVE_LEFT;
					else
						curMove = MOVE_RIGHT;
						*/
					sprite.move({ 0,(43 - sprite.getGlobalBounds().position.y) });
					//std::cout << "works" << std::endl;;
					inDoor = false;
					exitDoor = false;
					exitOnce = false;
				}
			}
		}
		doorTime.restart();
	}
}


/// <summary>
/// does the player jumping animation given ground
/// </summary>
/// <param name="angle">angle jumping at</param>
/// <param name="ground"></param>
/// <returns></returns>
bool Player::jump(double angle, std::vector<sf::FloatRect>* ground)
{
	t += 0.2;
	//parabolic equation for jump, pos keeps track of position while Mov uses pos to track how much movement is required each frame
	xMov = velo * cos(angle) * t - xPos;
	xPos = velo * cos(angle) * t;
	yMov = -0.5 * g * t * t + velo * sin(angle) * t - yPos;
	yPos = -0.5 * g * t * t + velo * sin(angle) * t;
	sprite.move({ xMov, -1 * yMov });
	view->move({ xMov, 0 });
	if(faceRight)
		curMove = JUMP_RIGHT;
	else
		curMove = JUMP_LEFT;
	for (int i = 0; i < ground->size(); i++)
	{
		if (sprite.getGlobalBounds().findIntersection(ground->at(i)) != std::nullopt&&t>0.5)
		{
			if (!faceRight)
				sprite.setTextureRect(moveLeft->nextFrame());
			else
				sprite.setTextureRect(moveRight->nextFrame());
			if(floor==0)
				sprite.move({ 0,(120-sprite.getGlobalBounds().position.y) });
			else
				sprite.move({ 0,(43 - sprite.getGlobalBounds().position.y) });
			xMov = 0;
			yMov = 0;
			xPos = 0;
			yPos = 0;
			return false;
		}
	}
	if (floor == 1)
	{
		for (int i = 0; i < ground1.size(); i++)
		{
			if (sprite.getGlobalBounds().findIntersection(ground1.at(i)) != std::nullopt && t > 0.5)
			{
				if (!faceRight)
					sprite.setTextureRect(moveLeft->nextFrame());
				else
					sprite.setTextureRect(moveRight->nextFrame());
				sprite.move({ 0,(120 - sprite.getGlobalBounds().position.y) });
				floor = 0;
				xMov = 0;
				yMov = 0;
				xPos = 0;
				yPos = 0;
				return false;
			}
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

