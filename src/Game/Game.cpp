#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "../Entity/Player/Player.h"
#include "../Entity/Door/Door.h"
#include "../Entity/Raill/Rail.h"
#include<vector>
#include<iostream>

//Constructor
Game::Game()
{
    // this MUST be called first. loads the textures.
    AnimationData::load();

	stage1.loadFromFile("res/Background/stage1(final).png");
    player = new Player();
    ground.push_back(sf::FloatRect({ 20.f,166.f }, { 1700.f,1.f }));
    ground.push_back(sf::FloatRect({ 1717.f,87.f }, { 46.f, 1.f }));
    ground.push_back(sf::FloatRect({ 1763.f,145.f }, { 48.f,1.f }));
    ground.push_back(sf::FloatRect({ 1811.f,203.f }, { 48.f, 1.f }));
    ground.push_back(sf::FloatRect({ 1859.f,273.f }, { 46.f,1.f }));
    ground.push_back(sf::FloatRect({ 1905.f,342.f }, { 51.f,1.f }));
}


Game::~Game()
{
    delete player;
}



//Runs the game
void Game::run()
{
	//doors
    Door* door = new Door(94, 113);
    Door* door2 = new Door(258, 113);
    Door* door3 = new Door(282, 42);
    Door* door4 = new Door(424, 112);
	Door* door5 = new Door(495, 42);
	Door* door6 = new Door(636, 112);
	Door* door7 = new Door(707, 112);
	Door* door9 = new Door(823, 41);
	Door* door10 = new Door(1012, 112);
	Door* door11 = new Door(1083, 42);
	Door* door12 = new Door(1200, 112);
	Door* door13 = new Door(1271, 112);
	Door* door14 = new Door(1388, 41);
	Door* door15 = new Door(1436, 41);
	Door* door16 = new Door(1483, 41);
	Door* door17 = new Door(1530, 41);
    std::vector<Entity*>& doors = Entity::getDoors();

    //rails
    Rail* rail = new Rail(82, 55);
    std::vector<Entity*>& rails = Entity::getRails();
    
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

    //debug objects
	bool debug = true;
    Rail* debugRail = new Rail(50, 50);
	Door* debugDoor = new Door(0, 0);
	debugDoor->changeOpacity(false);
    debugRail->changeOpacity(false);
    sf::Vector2f worldPos;

    //doors
    bool wPressed = false;


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
                case sf::Keyboard::Scan::F5:
                    debug = true;
                    break;
                case sf::Keyboard::Scan::F6:
					std::cout << window.mapPixelToCoords(sf::Mouse::getPosition()).x <<
                        ' ' << window.mapPixelToCoords(sf::Mouse::getPosition()).y << std::endl;
                    break;
                case sf::Keyboard::Scan::W:
                    wPressed = true;
					break;
                case sf::Keyboard::Scan::R:
                    player->setPos(sf::Vector2f(100, 120));
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
                    wPressed = false;
                    break;

                }
            }
        }
        //draw 
        window.clear();
        window.draw(stage1Sprite);
        //this is subject to change
        if (debug)
        {
            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition());
            debugRail->setPos(worldPos);
			debugRail->changeOpacity(false);
        }
        
        //testa
        window.draw(rectangle);

        //draw doors
        for (int i =0; i < doors.size(); i++)
        {
            window.draw(doors.at(i)->getSprite());
        }
        //draw rails
        for (int i = 0; i < rails.size(); i++)
        {
            window.draw(rails.at(i)->getSprite());
        }
        //enemy->update(player->getSprite().getPosition());
        window.draw(debugRail->getSprite());
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);
        window.draw(rectangle5);
        window.draw(rectangle6);
        // actions flags defines booleans in Game.cpp that are passed to the entity.
        // done this way to allow input to be read in Game.cpp
        char actionFlags = 0b0;
		if (wPressed) actionFlags |= 0b10000000;
        if (movingRight) actionFlags |= 0b00000001;
        if (movingLeft) actionFlags |= 0b00000010;
        if (movingRight&&jumping) actionFlags |= 0b00001000;
        if (jumping&&!movingRight&&!movingLeft) actionFlags |= 0b00000100;
        if (movingLeft && jumping) actionFlags |= 0b00010000;
        player->update(actionFlags,&ground);
        for (int i = 0; i < doors.size(); i++)
        {
            doors.at(i)->update(actionFlags, &ground);
        }
		debugDoor->update(actionFlags,&ground);

        //find which door is being collied with if "W" is pressed

        isColliding(actionFlags);
        //used to update all entites
		//draw the foreground
        window.setView(view);
        window.display();
        currentTick++; // keep track of the ticks that have passed
    }
}

//checks if any entities are colliding
void Game::isColliding(char actionFlags)
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
                    entities.at(i)->collide(entities.at(j), actionFlags);
                    entities.at(j)->collide(entities.at(i), actionFlags);
                }
             }
        }
    }
}


void deleteLevel()
{

}