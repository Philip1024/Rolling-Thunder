#include <SFML/Graphics.hpp>
#include<optional>
#pragma once


class Player
{
public:
	int sheetPos;
	std::optional<sf::Sprite> sprite;
	sf::Texture texture;
	//Player();
	//void updateRight();
};

