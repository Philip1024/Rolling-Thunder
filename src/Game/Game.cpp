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

//Constructor
Game::Game()
{
    // this MUST be called first. loads the textures.
    AnimationData::load();

	stage1.loadFromFile("res/Background/stage1(final).png");
    player = new Player();
    ground.push_back(sf::FloatRect({ 20.f,166.f }, { 1700.f,5.f }));
    ground.push_back(sf::FloatRect({ 1717.f,87.f }, { 46.f, 5.f }));
    ground.push_back(sf::FloatRect({ 1763.f,145.f }, { 48.f,5.f }));
    ground.push_back(sf::FloatRect({ 1811.f,203.f }, { 48.f, 5.f }));
    ground.push_back(sf::FloatRect({ 1859.f,273.f }, { 46.f,5.f }));
    ground.push_back(sf::FloatRect({ 1905.f,342.f }, { 51.f,5.f }));
    ground2.push_back(sf::FloatRect({ 132.f,84.f }, { 441.f,5.f }));
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
    std::vector<Entity*>& doors = Entity::getDoors();

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
    std::vector<Entity*>& rails = Entity::getRails();
    
    //for testing
    std::vector<sf::RectangleShape> groundSprites;

    for (sf::FloatRect rect : ground)
    {
        groundSprites.push_back(sf::RectangleShape(rect.size));
        groundSprites[groundSprites.size() - 1].setPosition(rect.position);
    }
    for (sf::FloatRect rect : ground2)
    {
        groundSprites.push_back(sf::RectangleShape(rect.size));
        groundSprites[groundSprites.size() - 1].setPosition(rect.position);
    }

    //debug objects
	//bool debug = true;
    //Rail* debugRail = new Rail(50, 50);
	//Door* debugDoor = new Door(0, 0);
	//debugDoor->changeOpacity(false);
   // debugRail->changeOpacity(false);
   // sf::Vector2f worldPos;

    //doors
    bool wPressed = false;
    int count = 0;//for testing

    //used to not have to wait for clock to reach 0.075 to move
    new Enemy(sf::Vector2f(200, 107)); // mem leak
	//The enemeyDoor spawn will allow for one door to spawn a enemy every six seconds
    //This is passed as a paramater through door update;

    sf::Clock enemySpawnClockTemp;
    sf::Clock* enemySpawnClock = &enemySpawnClockTemp;
    bool allowEnemySpawnTemp = true;
    bool* allowEnemyDoorSpawn = &allowEnemySpawnTemp;

	enemySpawnClock->restart();

    char dummy = 0;
    bool firstD = true;
    bool firstA = true;
    // if the player is moving right or left
    bool movingLeft = false, movingRight = false;
    //if player is shooting
    bool shooting = false;
    //used to determine height of jump
    double jumpHeight=0;
    //used to determine if jumping
    bool jumping = false;
    //used to determined if crouching
    bool crouching = false;
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

    std::vector<Entity*>& bullets = Entity::getBullets();
    std::vector<Entity*>& enemys = Entity::getEnemys();

    GUI gui;
    std::cout << enemys.size(); 
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
        //draw 
        window.clear();
        window.draw(stage1Sprite);
        //this is subject to change
        /*if (debug)
        {
            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition());
            debugRail->setPos(worldPos);
            debugRail->changeOpacity(false);
        }*/


      //  window.draw(debugRail->getSprite());
        for (sf::RectangleShape sprite : groundSprites)
            window.draw(sprite);

        // actions flags defines booleans in Game.cpp that are passed to the entity.
        // done this way to allow input to be read in Game.cpp
        char actionFlags = 0b0;
        if (wPressed) actionFlags |= 0b10000000;
        if (wPressed && jumping) actionFlags |= 0b01000000;
        if (movingRight) actionFlags |= 0b00000001;
        if (movingLeft) actionFlags |= 0b00000010;
        if (movingRight && jumping) actionFlags |= 0b00001000;
        if (jumping && !movingRight && !movingLeft && !wPressed) actionFlags |= 0b00000100;
        if (movingLeft && jumping) actionFlags |= 0b00010000;
        if (shooting) actionFlags |= 0b00100000;
        if (crouching && jumping) actionFlags |= 0b100000000;


        for (int i = 0; i < doors.size(); i++)
        {
            ((Door*)doors.at(i))->update(actionFlags, player->getSprite().getPosition().x, player->getSprite().getPosition().y, allowEnemyDoorSpawn, enemySpawnClock);
        }

        //update draws player so this is called before rail is drawn
        if (player->getFloor() == 1)
            player->update(actionFlags);

        //draw rails
        for (int i = 0; i < rails.size(); i++)
        {
            window.draw(rails.at(i)->getSprite());
        }

        //update draws player so this is called after rail is drawn

        //std::cout << "true" << std::endl;
        //enemy->update(player);

        //This is for the enemy spawning via door.
        if (enemySpawnClock->getElapsedTime().asSeconds() > 6)
        {
            *allowEnemyDoorSpawn = true;
        }

        //This is the main update for the door

        //debugDoor->update(actionFlags,&ground);
        if (player->getFloor() == 0)
            player->update(actionFlags);
        //update bullete and draw
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets.at(i)->update(actionFlags);
        }
        //enemy update
        for (int i = 0; i < enemys.size(); i++)
        {
            //check to see if enemy is dead
            if (!(Enemy*)enemys.at(i)->getAlive())
            {
                enemys.erase(std::remove(enemys.begin(), enemys.end(), enemys.at(i)), enemys.end());
            }
            else
            {
                ((Enemy*)enemys.at(i))->update(player);

            }
              
        }
        //find which door is being collied with if "W" is pressed
        isColliding(actionFlags);
        //gui.drawGUI(window);

        //used to update all entites
		//draw the foreground
        window.setView(view);
        window.display();
        currentTick++; // keep track of the ticks that have passed
        //std::cout << currentTick << std::endl;
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