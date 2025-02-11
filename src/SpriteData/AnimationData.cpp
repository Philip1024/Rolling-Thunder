#include "AnimationData.h"


void AnimationData::load()
{
	textureMap[ENEMY] = new sf::Texture("res/SpriteSheets/Enemy.png");
	textureMap[ALBATROSS] = new sf::Texture("res/SpriteSheets/Albatross.png");
	textureMap[DOOR] = new sf::Texture("res/SpriteSheets/Door.png");
}


void AnimationData::unload()
{
	for (std::pair<const TextureName, sf::Texture*> texture : textureMap)
		delete texture.second;
}


AnimationData::Section AnimationData::getSection(std::string sectionName)
{
	return sectionMap[toLowerCase(sectionName)];
}


std::string AnimationData::toLowerCase(std::string i)
{
	for (char& c : i)
		c = tolower(c);
	return i;
}
