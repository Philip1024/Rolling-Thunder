#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include<optional>


class Entity
{
public:
	Entity();
	static std::vector<Entity*>& getEntities() { return entities; }
	//virtual void collide(Entity* other) = 0;
	std::optional<sf::Sprite> sprite;
	//optional makes it so that sprite isn't
	//constructed until texture is loaded from file
	sf::Texture texture;
private:
	static std::vector<Entity*> entities;
};