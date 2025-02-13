#include "AnimationData.h"
std::unordered_map<AnimationData::TextureName, sf::Texture*> AnimationData::textureMap;
std::unordered_map<std::string, AnimationData::Section*> AnimationData::sectionMap;


void AnimationData::load()
{
	textureMap[ENEMY] = new sf::Texture("res/SpriteSheets/Enemy.png");
	textureMap[ALBATROSS] = new sf::Texture("res/SpriteSheets/Albatross.png");
	textureMap[DOOR] = new sf::Texture("res/SpriteSheets/Door.png");

	sectionMap["albatross_move_left"] = new Section("albatross_move_left", textureMap[ALBATROSS], 
		6, 1, sf::Vector2u(20, 60), sf::Vector2u(200, 117));
	sectionMap["albatross_move_right"] = new Section("albatross_move_left", textureMap[ALBATROSS],
		6, 1, sf::Vector2u(230, 60), sf::Vector2u(410, 117));

	sectionMap["door_open"] = new Section("door_open", textureMap[DOOR],
		3, 1, sf::Vector2u(215, 3), sf::Vector2u(347, 63));
}


void AnimationData::unload()
{
	for (std::pair<const TextureName, sf::Texture*> texture : textureMap)
		delete texture.second;
	for (std::pair<std::string, Section*> section : sectionMap)
		delete section.second;
}


AnimationData::Section* AnimationData::getSection(std::string sectionName)
{
	return sectionMap[toLowerCase(sectionName)];
}


std::string AnimationData::toLowerCase(std::string i)
{
	for (char& c : i)
		c = tolower(c);
	return i;
}


sf::IntRect AnimationData::Section::getFrame(unsigned int c) const
{
	sf::IntRect ret;
	unsigned int y = c / horizontalFrames;

	if (y > verticalFrames)
		throw std::exception("Getting invalid frame!"); // this will be the source of frustration perhaps

	unsigned int x = c % horizontalFrames;

	ret.position = sf::Vector2i(start.x + xSize*x, start.y + ySize*y);
	ret.size = sf::Vector2i(xSize, ySize);

	return ret;
}


sf::IntRect AnimationData::Section::getFrame(unsigned int x, unsigned int y) const
{
	return getFrame(horizontalFrames * y + x);
}
