#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "../Entity/Player/Player.h"
#include "../Entity/Door/Door.h"
#include<vector>
#include<iostream>

//Constructor
Game::Game()
{
    // this MUST be called first. loads the textures.
    AnimationData::load();

	stage1.loadFromFile("res/Background/stage1(final).png");
    player = new Player();
    ground.push_back(sf::FloatRect({ 20.f,167.f }, { 1720.f,166.f }));
    ground.push_back(sf::FloatRect({ 1717.f,88.f }, { 1763.f,87.f }));
    ground.push_back(sf::FloatRect({ 1763.f,146.f }, { 1811.f,145.f }));
    ground.push_back(sf::FloatRect({ 1811.f,204.f }, { 1859.f,203.f }));
    ground.push_back(sf::FloatRect({ 1859.f,274.f }, { 1905.f,273.f }));
    ground.push_back(sf::FloatRect({ 1905.f,343.f }, { 1956.f,342.f }));
}


Game::~Game()
{
    delete player;
}


//Runs the game
void Game::run()
{
    sf::RectangleShape rectangle(sf::Vector2f(1700, 1));
    rectangle.setPosition(sf::Vector2f(20, 159));
    //door 1
    Door* door = new Door(84,111); // this is memory leaking lol
    //used to not have to wait for clock to reach 0.075 to move
    Enemy* enemy = new Enemy(sf::Vector2f(160, 107)); // mem leak
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
    // what tick the game is on.
    unsigned int currentTick = 0;
	//window/clock setup
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Rolling Thunder");
    Entity::setWindow(&window);
    Entity::setCurrentTick(&currentTick);
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
                case sf::Keyboard::Scan::F:
                    jumping = true;
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
                case sf::Keyboard::Scan::F:
                    jumping = false;
                    break;
                }
            }
        }
       
        window.clear();
        window.draw(stage1Sprite);
        window.draw(rectangle);
        door->update(dummy);
        enemy->update(dummy);

        // actions flags defines booleans in Game.cpp that are passed to the entity.
        // done this way to allow input to be read in Game.cpp
        char actionFlags = 0b0;
        if (movingRight) actionFlags |= 0b00000001;
        if (movingLeft) actionFlags |= 0b00000010;
        if (movingRight&&jumping) actionFlags |= 0b00000100;
        player->update(actionFlags,ground);
        isColliding();
        //used to update all entites
		//draw the foreground
        window.setView(view);
        window.display();
        currentTick++; // keep track of the ticks that have passed
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
