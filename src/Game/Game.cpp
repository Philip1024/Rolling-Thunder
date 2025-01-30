#include "Game.h"
#include <SFML/Graphics.hpp>

//Constructor
Game::Game()
{
	stage1.loadFromFile("res/Background/stage1(final).png");
}


//Runs the game
void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Rolling Thunder");
	sf::Sprite stage1Sprite(stage1);
    stage1Sprite.setPosition({ 500,500 });
 

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
	
        window.clear();
		//draw the foreground 
		window.draw(stage1Sprite);
        window.display();
    }
}