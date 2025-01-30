#pragma once
#include <vector>
#include<SFML/Graphics.hpp>


class Entity
{
public:
	Entity();
	static std::vector<Entity*>& getEntities() { return entities; }
	virtual void collide(Entity* other) = 0;
	std::optional<sf::Sprite> sprite;
	sf::Texture* texture;
private:
	static std::vector<Entity*> entities;
};