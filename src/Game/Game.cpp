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
    // this MUST be called first. loads the textures.
    AnimationData::load();

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
    //door 1
    Door* door = new Door(84,111);
    //used to not have to wait for clock to reach 0.075 to move
    char dummy = 0;
    bool firstD = true;
    bool firstA = true;
    // if the player is moving right or left
    bool movingLeft = false, movingRight = false;
    //used to determine height of jump
    double jumpHeight=0;
    //used to determine if jumping
    bool jumping = false;
    //glogbal postion of the level
    double gamePosX = 0;
    double gamePosY = 0;
	//window/clock setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Rolling Thunder");
    Entity::setWindow(&window);
    window.setFramerateLimit(30);
	//Sprtie for the background
	sf::Sprite stage1Sprite(stage1);
    //main view subject to change 
    sf::View view(sf::FloatRect({ 0, 0 }, { 1920, 1080 }));
    Entity::setView(&view);
    //DO NOT CHANGE THESE VALUES! IT IS EXACT TO THE PIXELS OF THE IMAGE!
    view.setViewport(sf::FloatRect({ 0.f, -.1023f }, { 6.72f, 6.72f }));
    window.setKeyRepeatEnabled(false);

    //Main gameplay loop
    while (window.isOpen())
    {
        // event loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->scancode)
                {
                case sf::Keyboard::Scan::A:
                    movingLeft = true;
                    break;
                case sf::Keyboard::Scan::D:
                    movingRight = true;
                    break;
                }
            }
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyReleased->scancode)
                {
                case sf::Keyboard::Scan::A:
                    movingLeft = false;
                    break;
                case sf::Keyboard::Scan::D:
                    movingRight = false;
                    break;
                }
            }
        }
       
        window.clear();
        window.draw(stage1Sprite);
        door->update(dummy);

        // actions flags defines booleans in Game.cpp that are passed to the entity.
        // done this way to allow input to be read in Game.cpp
        char actionFlags = 0b0;
        if (movingRight) actionFlags |= 0b00000001;
        if (movingLeft) actionFlags |= 0b00000010;
        player->update(actionFlags);

        isColliding();
        //used to update all entites
		//draw the foreground
        window.setView(view);
        window.display();
    }
}


void Game::isColliding()
{
    std::vector<Entity*>& entities = Entity::getEntities();
    if (entities.size() > 1)
    {
        for (int i = 0; i < entities.size(); i++)
        {
             for (int j = i + 1; j < entities.size(); j++)
             {
                 if (entities.at(i)->getSprite().getGlobalBounds().findIntersection(entities.at(j)->getSprite().getGlobalBounds()))
                 {
                     entities.at(i)->collide(entities.at(j));
                     entities.at(j)->collide(entities.at(i));
                 }
             }
        }
    }
}
