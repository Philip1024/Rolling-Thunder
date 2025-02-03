#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include<optional>


class Entity
{
public:
	Entity();
	//static std::vector<Entity*>& getEntities() { return entities; }
	//virtual void collide(Entity* other) = 0;
	static std::optional<sf::Sprite> sprite;
	//static sf::Texture* texture;
	//virtual sf::Sprite sprite() = 0;
private:
	static std::vector<Entity*> entities;
};