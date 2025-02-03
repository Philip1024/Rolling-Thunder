#include "Player.h"
#include"../Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<optional>
Player::Player()
{
	texture.loadFromFile("res/SpriteSheets/Albatross.png");
}

sf::Sprite Player::sprite()
{
	sf::Vector2i position(x, 60);
	sf::Vector2i size(30, 60);

	return sf::Sprite(texture);


}

/*
sf::Sprite Player::sprite()
{
	Entity::texture->loadFromFile("res/SpriteSheets/Albatross.png");
	return sf::Sprite(*Entity::texture);
*/