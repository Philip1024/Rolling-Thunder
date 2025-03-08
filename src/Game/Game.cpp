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
    //ground.push_back(sf::FloatRect({ 1717.f,88.f }, { 1763.f,87.f }));
    ground.push_back(sf::FloatRect({ 1763.f,146.f }, { 1811.f,145.f }));
    ground.push_back(sf::FloatRect({ 1811.f,204.f }, { 1859.f,203.f }));
    ground.push_back(sf::FloatRect({ 1859.f,274.f }, { 1905.f,273.f }));
   // ground.push_back(sf::FloatRect({ 1905.f,343.f }, { 1956.f,342.f }));
}


Game::~Game()
{
    delete player;
}


//Runs the game
void Game::run()
{
    //for testing
    sf::RectangleShape rectangle(sf::Vector2f(1700, 1));
    sf::RectangleShape rectangle2(sf::Vector2f(46, 1));
    sf::RectangleShape rectangle3(sf::Vector2f(48, 1));
    sf::RectangleShape rectangle4(sf::Vector2f(48, 1));
    sf::RectangleShape rectangle5(sf::Vector2f(46, 1));
    sf::RectangleShape rectangle6(sf::Vector2f(51, 1));
    rectangle.setPosition(sf::Vector2f(20, 166));
    rectangle2.setPosition(sf::Vector2f(1717, 87));
    rectangle3.setPosition(sf::Vector2f(1763, 145));
    rectangle4.setPosition(sf::Vector2f(1811, 203));
    rectangle5.setPosition(sf::Vector2f(1859, 273));
    rectangle6.setPosition(sf::Vector2f(1905, 342));

    //door 1
    bool doorOpen = false;
    Door* door = new Door(94,113); // this is memory leaking lol
    //used to not have to wait for clock to reach 0.075 to move
    Enemy* enemy = new Enemy(sf::Vector2f(200, 107)); // mem leak
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
                case sf::Keyboard::Scan::W:
                    doorOpen = true;
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
                case sf::Keyboard::Scan::W:
                    doorOpen = false;
                    break;
                }
            }
        }
        window.clear();
        window.draw(stage1Sprite);
        window.draw(door->getSprite());
        window.draw(rectangle);
        enemy->update(player->getSprite().getPosition());

        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);
        window.draw(rectangle5);
        window.draw(rectangle6);
        // actions flags defines booleans in Game.cpp that are passed to the entity.
        // done this way to allow input to be read in Game.cpp
        char actionFlags = 0b0;
		if (doorOpen) actionFlags |= 0b10000000;
        if (movingRight) actionFlags |= 0b00000001;
        if (movingLeft) actionFlags |= 0b00000010;
        if (movingRight&&jumping) actionFlags |= 0b00001000;
        if (jumping&&!movingRight&&!movingLeft) actionFlags |= 0b00000100;
        if (movingLeft && jumping) actionFlags |= 0b00010000;
        player->update(actionFlags,&ground);
        door->update(actionFlags);
        isColliding();
        //used to update all entites
		//draw the foreground
        window.setView(view);
        window.display();
        currentTick++; // keep track of the ticks that have passed
    }
    delete door;
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
