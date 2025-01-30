#include "Game.h"
#include <SFML/Graphics.hpp>

//Constructor
Game::Game()
{
	stage1.loadFromFile("res/Background/stage1(final).png");
}


//Runs the game
void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 175 }), "Rolling Thunder");

   
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
        window.display();
    }
}