#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "../Entity/Player/Player.h"

//Constructor
Game::Game()
{
	stage1.loadFromFile("res/Background/stage1(final).png");
    player = new Player();
}


Game::~Game()
{
    delete player;



}


//Runs the game
void Game::run()
{
    //keeps track of time between sprite updates
    sf::Clock clock;
    //used to not have to wait for clock to reach 0.075 to move
    bool firstD = true;
    bool firstA = true;
    //glogbal postion of the level
    double gamePosX = 0;
    double gamePosY = 0;
	//window/clock setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Rolling Thunder");
    window.setFramerateLimit(60);
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
	    //check for input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
                if (clock.getElapsedTime().asSeconds() > 0.075f)
                {
                    view.move({ 5.5,0 });
                    gamePosX += .8;
                    player->updateRight();
                    clock.restart();
                }
			}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && gamePosX > 0)
            {
                if (clock.getElapsedTime().asSeconds() > 0.075f)
                {
                    view.move({ -5.5,0 });
                    gamePosX -= .8;
                    player->updateLeft();
                    clock.restart();
                }
               
            }
        }
        window.clear();
		//draw the foreground 
        window.setView(view);
		window.draw(stage1Sprite);
        window.draw(*player->sprite);
        //window.draw(player.sprite);
        window.display();
    }
}
