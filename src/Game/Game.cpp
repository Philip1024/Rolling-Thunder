#include "Game.h"
#include <SFML/Graphics.hpp>
#include "../Entity/Player/Player.h"

//Constructor
Game::Game()
{
	stage1.loadFromFile("res/Background/stage1(final).png");
}


//Runs the game
void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 175 }), "Rolling Thunder");
    //Player player;
    //player.texture.loadFromFile()
   
	sf::Sprite stage1Sprite(stage1);
    stage1Sprite.setPosition({ 0, 0 });
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
	
        window.clear();
		window.draw(stage1Sprite);
        //window.draw(player.sprite);
        window.display();
    }
}