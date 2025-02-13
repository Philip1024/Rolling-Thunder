#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "../Entity/Player/Player.h"
#include "../Entity/Door/Door.h"

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
    // this must be calle
    AnimationData::load();
    //door 1
    Door* door = new Door(84,111);
    //keeps track of time between sprite updates
    sf::Clock clock;
    //used to not have to wait for clock to reach 0.075 to move

    bool firstD = true;
    bool firstA = true;
    //used to determine height of jump
    double jumpHeight=0;
    //used to determine if jumping
    bool jumping = false;
    //glogbal postion of the level
    double gamePosX = 0;
    double gamePosY = 0;
	//window/clock setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Rolling Thunder");
    window.setFramerateLimit(30);
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
            
            
            if (clock.getElapsedTime().asSeconds() > 0.05f)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && gamePosX > 0)
                {
                    view.move({ -7.5,0 });
                    gamePosX -= .8;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {

                        view.move({ 7.5,0 });
                        gamePosX += .8;
                }
                player->update();
                clock.restart();
            }
        }
        //used to update all entites
        window.clear();
		//draw the foreground 
        window.setView(view);
		window.draw(stage1Sprite);
        window.draw(*player->sprite);
		//window.draw(*door->sprite);
        window.display();
    }
}


void Game::isColliding()
{
    static std::vector<Entity*> entities = Entity::getEntities();
    if (entities.size() > 1)
    {
        for (int i = 0; i < entities.size(); i++)
        {
             for (int j = i + 1; j < entities.size(); j++)
             {
                 if (entities.at(i)->sprite->getGlobalBounds().findIntersection(entities.at(j)->sprite->getGlobalBounds()))
                 {
                     entities.at(i)->collide(entities.at(j));
                     entities.at(j)->collide(entities.at(i));
                 }
             }
        }



    }




}
