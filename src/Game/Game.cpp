#include <SFML/Graphics.hpp>
#include "Game.h"


void Game::run()
{
	sf::RenderWindow window(sf::VideoMode({ 425, 822 }), "SFML works!");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.display();
    }


}