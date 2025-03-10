#include "AnimationData.h"
std::unordered_map<AnimationData::TextureName, sf::Texture*> AnimationData::textureMap;
std::unordered_map<std::string, AnimationData::Section*> AnimationData::sectionMap;


void AnimationData::load()
{
	textureMap[ENEMY] = new sf::Texture("res/SpriteSheets/Enemy.png");
	textureMap[ENEMY_FLIPPED] = new sf::Texture("res/SpriteSheets/Enemy_flipped.png");
	textureMap[ALBATROSS] = new sf::Texture("res/SpriteSheets/Albatross.png");
	textureMap[DOOR] = new sf::Texture("res/SpriteSheets/Door(1).png");
	auto rightToLeftFunction = [](unsigned int& curFrame, unsigned int maxFrames) -> void { // LAMBDA
		if (curFrame == 0)
			curFrame = maxFrames;
		curFrame--;
	};
	sectionMap["albatross_move_left"] = new Section(textureMap[ALBATROSS], 
		6, 1, sf::Vector2u(20, 60), sf::Vector2u(200, 117));
	getSection("albatross_move_left")->setNextFrameFunction(rightToLeftFunction);

	sectionMap["albatross_move_right"] = new Section(textureMap[ALBATROSS],
		6, 1, sf::Vector2u(230, 60), sf::Vector2u(410, 117));
	sectionMap["albatross_standard_right_jump"] = new Section(textureMap[ALBATROSS],
		1, 2, sf::Vector2u(230, 550), sf::Vector2u(260, 650));
	sectionMap["albatross_standard_left_jump"] = new Section(textureMap[ALBATROSS],
		1, 2, sf::Vector2u(165, 550), sf::Vector2u(195, 650));
	sectionMap["albatross_falling_left"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(22, 540), sf::Vector2u(70, 600));
	sectionMap["albatross_falling_right"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(353, 540), sf::Vector2u(401, 600));


	sectionMap["enemy_move_left"] = new Section(textureMap[ENEMY_FLIPPED],
		7, 1, sf::Vector2u(800, 0), sf::Vector2u(1024, 64));
	getSection("enemy_move_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["enemy_move_right"] = new Section(textureMap[ENEMY],
		7, 1, sf::Vector2u(0, 0), sf::Vector2u(224, 64));
	sectionMap["enemy_idle_sneak"] = new Section(textureMap[ENEMY],
		9, 1, sf::Vector2u(160, 78), sf::Vector2u(494, 127));
	sectionMap["enemy_idle_right"] = new Section(textureMap[ENEMY],
		2, 1, sf::Vector2u(928, 8), sf::Vector2u(992, 61));
	sectionMap["enemy_shoot_right"] = new Section(textureMap[ENEMY],
		3, 1, sf::Vector2u(123, 128), sf::Vector2u(266, 189));
	sectionMap["door_open"] = new Section(textureMap[DOOR],
		4, 1, sf::Vector2u(24, 2), sf::Vector2u(222, 62));
	sectionMap["door_close"] = new Section(textureMap[DOOR],
		4, 1, sf::Vector2u(24, 2), sf::Vector2u(222, 62));
	getSection("door_close")->setNextFrameFunction(rightToLeftFunction);
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


sf::IntRect AnimationData::SectionData::nextFrame()
{
	linkedSection->getNextFrameFunction()(curFrame, linkedSection->getMaxFrames());
	return linkedSection->getFrame(curFrame);
}