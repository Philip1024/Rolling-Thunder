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
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Rolling Thunder");
	//Sprtie for the background
	sf::Sprite stage1Sprite(stage1);
    //main view subject to change 
    sf::View view(sf::FloatRect({ 0, 0 }, { 1920, 1080 }));
    //DO NOT CHANGE THESE VALUES! IT IS EXACT TO THE PIXELS OF THE IMAGE!
    view.setViewport(sf::FloatRect({ 0.f, -.1023f }, { 6.72, 6.72 }));
 
    //Main gameplay loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear();
		//draw the foreground 
        window.setView(view);
		window.draw(stage1Sprite);
        //window.draw(player.sprite);
        window.display();
    }
}