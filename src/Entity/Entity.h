#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include<optional>
#include "../SpriteData/AnimationData.h"


class Entity
{
public:
	Entity(sf::Texture* initTexture);
	
	// this does not check collision, it is called when entities collide
	virtual void collide(Entity* other,char actionFlags) {}
	// entities are expected to do their functions and draw themselves in this method
	virtual void update(char actionFlags) { window->draw(sprite); }
	const sf::Sprite& getSprite() const { return sprite;  }
	static std::vector<Entity*>& getEntities() { return entities; }
	static std::vector<Entity*>& getDoors() { return doors; }
	// call these methods early or else unspecified behavior
	static void setWindow(sf::RenderWindow* w) { window = w; }
	static void setView(sf::View* v) { view = v; }
	static void setCurrentTick(unsigned int* t) { currentTick = t; }
	static std::vector<Entity*> doors;
protected:
	// optional makes it so that sprite isn't
	// constructed until texture is loaded from file
	sf::Sprite sprite;
	static sf::View* view;
	static unsigned int& getCurrentTick() { return *currentTick; }
	static sf::RenderWindow* window;
private:
	static unsigned int* currentTick;
	static std::vector<Entity*> entities;
};