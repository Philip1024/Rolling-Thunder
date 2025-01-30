#include <SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"


Player::Player()
{
    if (!texture.loadFromFile("res/SpriteSheets/Albatross.png"))
    {
        std::cout << "fail" << std::endl;
    }
    sprite.emplace(texture);
    sprite.setPosition(sf::Vector2f(212, 411));
    sheetPos = 200;
    sf::Vector2i position(sheetPos, 60);
    sf::Vector2i size(30, 60);
    sf::IntRect r2(position, size);
    sprite.setTextureRect(r2);
}


void Player::updateRight()
{
    if (sheetPos == 380)
        sheetPos = 230;
    else
        sheetPos += 30;
    sf::Vector2i position(sheetPos, 60);
    sf::Vector2i size(30, 60);
    sf::IntRect r2(position, size);
    sprite.setTextureRect(r2);


}