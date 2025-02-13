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


void Player::update()
{
	if (animationFrame > 5)
		animationFrame = 0;
	if (animationFrame < 0)
		animationFrame = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		sprite->setTextureRect(AnimationData::getSection("albatross_move_right")->getFrame(animationFrame++));
		sprite->move({ 7.5,0 });//not exact yet

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		sprite->setTextureRect(AnimationData::getSection("albatross_move_left")->getFrame(animationFrame--));
		sprite->move({ -7.5,0 });//not exact yet
		faceRight = false;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		sprite->setTextureRect(AnimationData::getSection("albatross_move_left")->getFrame(animationFrame--));
		sprite->move({ -7.5,0 });//not exact yet
		faceRight = false;

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