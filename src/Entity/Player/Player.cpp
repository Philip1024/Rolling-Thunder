#include<SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"


Player::Player()
{
	if (!texture.loadFromFile("res/SpriteSheets/Albatross.png"))
	{
		std::cout << "Fail";
	}
	sprite.setTexture(texture);


}