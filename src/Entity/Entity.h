#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include<optional>


class Entity
{
public:
	Entity();
	static std::vector<Entity*>& getEntities() { return entities; }
	// this does not check collision, it is called when entities collide
	virtual void collide(Entity* other) {}
	virtual void update();
	std::optional<sf::Sprite> sprite;
	//optional makes it so that sprite isn't
	//constructed until texture is loaded from file
	sf::Texture texture;
private:
	static std::vector<Entity*> entities;
};