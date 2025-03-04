#include "Entity.h"
std::vector<Entity*> Entity::entities;
sf::View* Entity::view = nullptr;
sf::RenderWindow* Entity::window = nullptr;
unsigned int* Entity::currentTick = nullptr;

Entity::Entity(sf::Texture* initTexture)
	: sprite(sf::Sprite(*initTexture))
{
	entities.push_back(this);
}
