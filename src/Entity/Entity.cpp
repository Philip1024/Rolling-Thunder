#include "Entity.h"
std::vector<Entity*> Entity::entities;
std::vector<Entity*> Entity::doors;
std::vector<Entity*> Entity::rails;
std::vector<Entity*> Entity::bullets;
std::vector<Entity*> Entity::enemys;
sf::View* Entity::view = nullptr;
sf::RenderWindow* Entity::window = nullptr;
unsigned int* Entity::currentTick = nullptr;

Entity::Entity(sf::Texture* initTexture)
	: sprite(sf::Sprite(*initTexture))
{
	entities.push_back(this);
}

