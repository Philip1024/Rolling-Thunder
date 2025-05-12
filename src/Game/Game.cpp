#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include "../Entity/Player/Player.h"
#include "../Entity/Door/Door.h"
#include "../Entity/Raill/Rail.h"
#include "../Entity/Bullet/Bullet.h"
#include "../Entity/Enemy/Enemy.h"
#include<vector>
#include<iostream>

/*
Change mode/screen using GameState: see the switch in main gameplay loop
 */
//Constructor
Game::Game()
    : stage1Sprite(stage1), gui(&credits)
{
    stage1.loadFromFile("res/Background/stage1(final).png");
    player = new Player();
    ground.push_back(sf::FloatRect({ 20.f,166.f }, { 1700.f,5.f }));
    ground.push_back(sf::FloatRect({ 1717.f,87.f }, { 46.f, 5.f }));
    ground.push_back(sf::FloatRect({ 1763.f,145.f }, { 48.f,5.f }));
    ground.push_back(sf::FloatRect({ 1811.f,203.f }, { 48.f, 5.f }));
    ground.push_back(sf::FloatRect({ 1859.f,273.f }, { 46.f,5.f }));
    ground.push_back(sf::FloatRect({ 1905.f,342.f }, { 51.f,5.f }));
    ground2.push_back(sf::FloatRect({ 132.f,84.f }, { 441.f,5.f }));
    ground2.push_back(sf::FloatRect({ 764.f,87.f }, { 375.f,5.f }));
    ground2.push_back(sf::FloatRect({ 1952.f,415.f }, { 1650.f,5.f }));

    window.setSize({(unsigned int)(1920.f * scale), (unsigned int)(1080.f * scale)});

    stage1Sprite = sf::Sprite(stage1);
}


Game::~Game()
{
    delete player;
}



//Runs the game
void Game::run()
{
	//doors
    new Door(94, 113);
    new Door(258, 113);
    new Door(282, 42);
    new Door(424, 112);
	new Door(495, 42);
	new Door(636, 112);
	new Door(707, 112);
	new Door(823, 41);
	new Door(1012, 112);
	new Door(1083, 42);
	new Door(1200, 112);
	new Door(1271, 112);
	new Door(1388, 41);
	new Door(1436, 41);
	new Door(1483, 41);
	new Door(1530, 41);

    //rails
    //Rail* rail = new Rail(82, 55);
    new Rail(126, 64);
    new Rail(171, 64);
    new Rail(216, 64);
    new Rail(261, 64);
    new Rail(306, 64);
    new Rail(351, 64);
    new Rail(396, 64);
    new Rail(441, 64);
    new Rail(486, 64);
    new Rail(531, 64);
    new Rail(762, 64);
    new Rail(807, 64);
    new Rail(852, 64);
    new Rail(897, 64);
    new Rail(942, 64);
    new Rail(987, 64);
    new Rail(1032, 64);
    new Rail(1075, 64);
    new Rail(1322, 64);
    new Rail(1365, 64);
    new Rail(1408, 64);
    new Rail(1451, 64);
    new Rail(1494, 64);
    new Rail(1537, 64);
    new Rail(1580, 64);
    new Rail(1623, 64);
    new Rail(1666, 64);
    new Rail(1709, 64);
    
    // for testing
    for (sf::FloatRect rect : ground)
    {
        groundDebugSprites.push_back(sf::RectangleShape(rect.size));
        groundDebugSprites[groundDebugSprites.size() - 1].setPosition(rect.position);
    }
    for (sf::FloatRect rect : ground2)
    {
        groundDebugSprites.push_back(sf::RectangleShape(rect.size));
        groundDebugSprites[groundDebugSprites.size() - 1].setPosition(rect.position);
    }

    //debug objects
	//bool debug = true;
    //Rail* debugRail = new Rail(50, 50);
	//Door* debugDoor = new Door(0, 0);
	//debugDoor->changeOpacity(false);
   // debugRail->changeOpacity(false);
   // sf::Vector2f worldPos;

    enemySpawnClock->restart();
    new Enemy(sf::Vector2f(200, 107),false); // mem leak

    //window/clock setup
    Entity::setWindow(&window);
    Entity::setCurrentTick(&currentTick);

    window.setFramerateLimit(30);
	
    //main mainView subject to change 
   
    Entity::setView(&mainView);
    //DO NOT CHANGE THESE VALUES! IT IS EXACT TO THE PIXELS OF THE IMAGE!
    mainView.setViewport(sf::FloatRect({ 0.f, -.1023f }, { 6.72f, 6.72f }));
    window.setKeyRepeatEnabled(false);

    //Main gameplay loop
    while (window.isOpen())
    {
        // event loop, input is handled here
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
                    gameState = GAMEPLAY;
                    break;
                case sf::Keyboard::Scan::D:
                    movingRight = true;
                    break;
                case sf::Keyboard::Scan::F:
                    jumping = true;
                    break;
                case sf::Keyboard::Scan::F5:
                    //debug = true;
                    break;
                case sf::Keyboard::Scan::F6:
					std::cout << window.mapPixelToCoords(sf::Mouse::getPosition()).x <<
                        ' ' << window.mapPixelToCoords(sf::Mouse::getPosition()).y << std::endl;
                    break;
                case sf::Keyboard::Scan::W:
                    wPressed = true;
					break;
                case sf::Keyboard::Scan::R:
                    shooting = true;
                    break;
                case sf::Keyboard::Scan::S:
                    crouching = true;
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
                case sf::Keyboard::Scan::R:
                    shooting = false;
                    break;
                case sf::Keyboard::Scan::S:
                    crouching = false;
                    break;
                case sf::Keyboard::Scan::K:
                    AnimationData::reloadTextures();
                    break;
                }
            }
        }

        // actions flags defines booleans in Game.cpp that are passed to the entity.
        // done this way to allow input to be read in Game.cpp
        //actionflags binary value must be under 128
        char actionFlags = 0b0;
        if (wPressed&&!jumping) actionFlags |= 0b01000001;
        if (wPressed && jumping) actionFlags |= 0b01000000;
        if (movingRight&&!jumping) actionFlags |= 0b00000001;
        if (movingLeft && !jumping) actionFlags |= 0b00000010;
        if (movingRight && jumping) actionFlags |= 0b00001000;
        if (jumping && !movingRight && !movingLeft && !wPressed&&!crouching) actionFlags |= 0b00000100;
        if (movingLeft && jumping) actionFlags |= 0b00010000;
        if (shooting) actionFlags |= 0b00100000;
        if (crouching && jumping) actionFlags |= 0b01000010;

        window.clear();
        //gameState = START;
        switch (gameState)
        {
        case START:
            runStartBehavior();
	        break;
        case GAMEPLAY:
            runGameplayBehavior(actionFlags);
	        break;
        case LOSE:
            //runLoseBehavior()
	        break;
        case WIN:
	        break;
        }

        window.display();
    }

}

//This method iterates through the entities vector with i being one less the j 
//to allow for comparison.
void Game::isColliding(char actionFlags)
{
    std::vector<Entity*>& entities = Entity::getEntities();
    if (entities.size() > 1)
    {
        for (int i = 0; i < entities.size(); i++)
        {
             for (int j = i + 1; j < entities.size(); j++)
             {
                Rail* railCast = dynamic_cast<Rail*>(entities.at(i));
                Rail* railCast2 = dynamic_cast<Rail*>(entities.at(j));
                Player* playerCast = dynamic_cast<Player*>(entities.at(i));
                Player* playerCast2 = dynamic_cast<Player*>(entities.at(j));
                Door* doorCast = dynamic_cast<Door*>(entities.at(i));
                Door* doorCast2 = dynamic_cast<Door*>(entities.at(j));
                Bullet* bulletCast = dynamic_cast<Bullet*>(entities.at(i));
                Bullet* bulletCast2 = dynamic_cast<Bullet*>(entities.at(j));
                Enemy* enemyCast = dynamic_cast<Enemy*>(entities.at(i));
                Enemy* enemyCast2 = dynamic_cast<Enemy*>(entities.at(j));
                // rail player collision
                if ((playerCast!=nullptr&&railCast2!=nullptr))
                {
                    if (entities.at(i)->getSprite().getPosition().x>railCast2->getFront())
                    {
                        if (entities.at(i)->getSprite().getPosition().x < railCast2->getBack())
                        {
                            entities.at(i)->collide(entities.at(j), actionFlags);
                            entities.at(j)->collide(entities.at(i), actionFlags);
                        }
                    }
                }
                else if ((railCast != nullptr && playerCast2 != nullptr))
                {
                    if (entities.at(j)->getSprite().getPosition().x > railCast->getFront())
                    {
                        if (entities.at(j)->getSprite().getPosition().x < railCast->getBack())
                        {
                            entities.at(i)->collide(entities.at(j), actionFlags);
                            entities.at(j)->collide(entities.at(i), actionFlags);
                        }
                    }
                }
                
                // player door collisions
                else if ((playerCast != nullptr && doorCast2 != nullptr))
                {
                    if (entities.at(i)->getSprite().getPosition().x > doorCast2->getFront())
                    {
                        if (entities.at(i)->getSprite().getPosition().x < doorCast2->getBack())
                        {
                            if (entities.at(i)->getSprite().getGlobalBounds().findIntersection(entities.at(j)->getSprite().getGlobalBounds()))
                            {
                                entities.at(i)->collide(entities.at(j), actionFlags);
                                entities.at(j)->collide(entities.at(i), actionFlags);
                            }
                        }
                    }
                }
                else if (playerCast2 != nullptr && doorCast != nullptr)
                {
                    if (entities.at(j)->getSprite().getPosition().x > doorCast->getFront())
                    {
                        if (entities.at(j)->getSprite().getPosition().x < doorCast->getBack())
                        {
                            if (entities.at(i)->getSprite().getGlobalBounds().findIntersection(entities.at(j)->getSprite().getGlobalBounds()))
                            {
                                entities.at(i)->collide(entities.at(j), actionFlags);
                                entities.at(j)->collide(entities.at(i), actionFlags);
                            }
                        }
                    }
                }
                //This if for deletion of enemy and bullet
                else if (enemyCast != nullptr && bulletCast2 != nullptr)
                {
                    if (entities.at(i)->getSprite().getGlobalBounds().findIntersection(entities.at(j)->getSprite().getGlobalBounds()))
                    {
                        entities.at(i)->collide(entities.at(j), actionFlags);
                        entities.at(j)->collide(entities.at(i), actionFlags);

                        //this deletes the enemy from the entities vector;
                        entities.erase(std::remove(entities.begin(), entities.end(), entities.at(i)), entities.end());
                        //this deletes the bullet from the entities vector.
                        j--;
                        entities.erase(std::remove(entities.begin(), entities.end(), entities.at(j)),entities.end());
                        i--;
                    }
                }
                else if (enemyCast2 != nullptr && bulletCast != nullptr)
                {
                    if (entities.at(i)->getSprite().getGlobalBounds().findIntersection(entities.at(j)->getSprite().getGlobalBounds()))
                    {
                        entities.at(i)->collide(entities.at(j), actionFlags);
                        entities.at(j)->collide(entities.at(i), actionFlags);
                        //this deletes the enemy from the entities vector;
                        entities.erase(std::remove(entities.begin(), entities.end(), entities.at(i)), entities.end());
                        //this deletes the bullet from the entities vector.
                        j--;
                        entities.erase(std::remove(entities.begin(), entities.end(), entities.at(j)), entities.end());
                        i--;
                    }
                }
                else
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
}


void deleteLevel()
{

}


void Game::runStartBehavior()
{
    // 5 to add credit 6 to start
    if (isKeyPressed(sf::Keyboard::Key::Num5) && credits < 9)
        credits++;
    if (isKeyPressed(sf::Keyboard::Key::Num6) && credits > 0)
    {
        gameState = GAMEPLAY;
        credits--;
    }

    window.setView(guiView);
    if (credits > 0)
        gui.changeScreen(GUI::SELECT_1);
    else
        gui.changeScreen(GUI::MAIN_MENU);

    gui.drawGUI(window);
    window.setView(mainView);

    
}


void Game::runGameplayBehavior(char actionFlags)
{
    //draw 
    window.draw(stage1Sprite);
    //this is subject to change
    /*if (debug)
    {
        worldPos = window.mapPixelToCoords(sf::Mouse::getPosition());
        debugRail->setPos(worldPos);
        debugRail->changeOpacity(false);
    }*/


    //  window.draw(debugRail->getSprite());
    for (sf::RectangleShape sprite : groundDebugSprites)
        window.draw(sprite);

    for (int i = 0; i < doors.size(); i++)
        ((Door*)doors.at(i))->update(actionFlags, player->getSprite().getPosition().x, player->getSprite().getPosition().y, allowEnemyDoorSpawn, enemySpawnClock);
    

    //update draws player so this is called before rail is drawn
    if (player->getFloor() == 1)
    {
        player->update(actionFlags);
    }

    //draw rails
    for (int i = 0; i < rails.size(); i++)
        window.draw(rails.at(i)->getSprite());

    //update draws player so this is called after rail is drawn

    //std::cout << "true" << std::endl;
    //enemy->update(player);

    //This is for the enemy spawning via door.
    if (enemySpawnClock->getElapsedTime().asSeconds() > 6)
        *allowEnemyDoorSpawn = true;

    //This is the main update for the door

    //debugDoor->update(actionFlags,&ground);
    if (player->getFloor() == 0)
        player->update(actionFlags);
    //update bullete and draw
    for (int i = 0; i < bullets.size(); i++)
        bullets.at(i)->update(actionFlags);


    //enemy update
    for (int i = 0; i < enemies.size(); i++)
    {
        //check to see if enemy is dead
        if (!((Enemy*)enemies.at(i))->getAlive())
        {
            std::cout << "removed";
            delete enemies.at(i);
            enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies.at(i)), enemies.end());
        }
        else
            ((Enemy*)enemies.at(i))->update(player);
    }
    //find which door is being collied with if "W" is pressed
    isColliding(actionFlags);

    /*window.setView(guiView);
    gui.changeScreen(GUI::INGAME);
    gui.drawGUI(window);*/
    window.setView(mainView);

    //used to update all entites
    //draw the foreground
    currentTick++; // keep track of the ticks that have passed
    //std::cout << currentTick << std::endl;
}