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
    sf::View view(sf::FloatRect({ 0, 0 }, { 1920, 1080 }));
    view.setViewport(sf::FloatRect({ 0.f, 0.f }, { 6.2, 6.2 }));
 

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();



        }
	
        window.clear();
		//draw the foreground 
        window.setView(view);
		window.draw(stage1Sprite);
        window.display();
    }
}