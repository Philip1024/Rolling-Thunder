#pragma once
#include <vector>
#include<SFML/Graphics.hpp>


class Entity
{
public:
	Entity();
	static std::vector<Entity*>& getEntities() { return entities; }
	virtual void collide(Entity* other) = 0;
	sf::Sprite sprite;
	static sf::Texture* texture;
private:
	static std::vector<Entity*> entities;
};