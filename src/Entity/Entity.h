#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include<optional>


class Entity
{
public:
	Entity(sf::Texture* initTexture);
	
	// this does not check collision, it is called when entities collide
	virtual void collide(Entity* other) {}
	// entities are expected to do their functions and draw themselves in this method
	virtual void update(char actionFlags) { window->draw(sprite); }

	const sf::Sprite& getSprite() const { return sprite;  }

	static std::vector<Entity*>& getEntities() { return entities; }
	static void setWindow(sf::RenderWindow* w) { window = w; }
	static void setView(sf::View* v) { view = v; }
protected:
	// optional makes it so that sprite isn't
	// constructed until texture is loaded from file
	sf::Sprite sprite;
	static sf::View* view;
private:
	static std::vector<Entity*> entities;
	static sf::RenderWindow* window;
};