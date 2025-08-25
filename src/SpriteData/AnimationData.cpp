#include "AnimationData.h"
#include<iostream>
std::unordered_map<AnimationData::TextureName, sf::Texture*> AnimationData::textureMap;
std::unordered_map<std::string, AnimationData::Section*> AnimationData::sectionMap;


void AnimationData::load()
{
	for (unsigned int i = 0; i < TextureName::SIZE; i++)
		textureMap[(TextureName)i] = new sf::Texture();

	reloadTextures();
	auto rightToLeftFunction = [](unsigned int& curFrame, unsigned int maxFrames) -> void { // LAMBDA
		if (curFrame == 0)
			curFrame = maxFrames;
		curFrame--;
	};

	//player
	sectionMap["albatross_move_left"] = new Section(textureMap[ALBATROSS], 
		6, 1, sf::Vector2u(20, 60), sf::Vector2u(200, 120));
	getSection("albatross_move_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["albatross_move_right"] = new Section(textureMap[ALBATROSS],
		6, 1, sf::Vector2u(230, 60), sf::Vector2u(410, 120));
	sectionMap["albatross_stand_right"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(323, 0), sf::Vector2u(341, 58));
	sectionMap["albatross_stand_left"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(83, 0), sf::Vector2u(101, 58));
	sectionMap["albatross_standard_right_jump"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(230, 550), sf::Vector2u(260, 600));
	sectionMap["albatross_standard_left_jump"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(165, 550), sf::Vector2u(195, 600));
	sectionMap["albatross_falling_left"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(22, 540), sf::Vector2u(70, 600));
	sectionMap["albatross_falling_right"] = new Section(textureMap[ALBATROSS],
		1, 1, sf::Vector2u(353, 540), sf::Vector2u(401, 600));
	sectionMap["albatross_walk_in_door"] = new Section(textureMap[ALBATROSS],
		1, 3, sf::Vector2u(195, 180), sf::Vector2u(230, 358));
	getSection("albatross_walk_in_door")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["albatross_walk_out_door"] = new Section(textureMap[ALBATROSS],
		1, 3, sf::Vector2u(195, 0), sf::Vector2u(230, 180));
	sectionMap["albatross_shooting_left"] = new Section(textureMap[ALBATROSS],
		3, 1, sf::Vector2u(31, 243), sf::Vector2u(185, 295));
	sectionMap["albatross_shooting_right"] = new Section(textureMap[ALBATROSS],
		3, 1, sf::Vector2u(238, 241), sf::Vector2u(391, 294));
	getSection("albatross_shooting_right")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["albatross_jumping_to_rail_right"] = new Section(textureMap[ALBATROSS],
		2, 1, sf::Vector2u(229, 174), sf::Vector2u(285, 241));
	sectionMap["albatross_jumping_to_rail_left"] = new Section(textureMap[ALBATROSS],
		2, 1, sf::Vector2u(137, 175), sf::Vector2u(196, 241));
	getSection("albatross_jumping_to_rail_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["albatross_climbing_onto_rail_right"] = new Section(textureMap[ALBATROSS],
		2, 2, sf::Vector2u(285, 368), sf::Vector2u(406, 473));
	sectionMap["albatross_climbing_onto_rail_left"] = new Section(textureMap[ALBATROSS],
		2, 2, sf::Vector2u(17, 368), sf::Vector2u(135, 473));
	getSection("albatross_climbing_onto_rail_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["albatross_climbing_off_rail_right"] = new Section(textureMap[ALBATROSS],
		2, 2, sf::Vector2u(285, 368), sf::Vector2u(406, 473));
	sectionMap["albatross_climbing_off_rail_left"] = new Section(textureMap[ALBATROSS],
		2, 2, sf::Vector2u(17, 368), sf::Vector2u(135, 473));
	getSection("albatross_climbing_off_rail_right")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["albatross_die_right"] = new Section(textureMap[ALBATROSS],
		3, 2, sf::Vector2u(238, 660), sf::Vector2u(402, 779));
	sectionMap["albatross_die_left"] = new Section(textureMap[ALBATROSS],
		3, 2, sf::Vector2u(19, 660), sf::Vector2u(187, 779));
	getSection("albatross_die_left")->setNextFrameFunction(rightToLeftFunction);

	//enemies
	sectionMap["enemy_move_left"] = new Section(textureMap[ENEMY],
		5, 1, sf::Vector2u(0, 320), sf::Vector2u(48, 64), true);
	getSection("enemy_move_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["enemy_move_right"] = new Section(textureMap[ENEMY],
		5, 1, sf::Vector2u(0, 192), sf::Vector2u(48, 64), true);
	sectionMap["enemy_idle_sneak"] = new Section(textureMap[ENEMY],
		9, 1, sf::Vector2u(0, 384), sf::Vector2u(48, 64), true);
	sectionMap["enemy_idle_right"] = new Section(textureMap[ENEMY],
		2, 1, sf::Vector2u(0, 512), sf::Vector2u(48, 64), true);
	sectionMap["enemy_shoot_right"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(0, 0), sf::Vector2u(48, 64), true);
	sectionMap["enemy_shoot_left"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(0, 64), sf::Vector2u(48, 64), true);
	getSection("enemy_shoot_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["enemy_punch_right"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(0, 704), sf::Vector2u(64, 64), true);
	sectionMap["enemy_punch_left"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(0, 768), sf::Vector2u(64, 64), true);
	getSection("enemy_punch_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["enemy_hit_left"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(590, 165), sf::Vector2u(64,55), true);
	sectionMap["enemy_hit_right"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(589, 92), sf::Vector2u(64, 55), true);
	getSection("enemy_hit_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["enemy_dissolve_left"] = new Section(textureMap[ENEMY],
		2, 5, sf::Vector2u(406, 1), sf::Vector2u(84, 19), true);
	sectionMap["enemy_dissolve_right"] = new Section(textureMap[ENEMY],
		2, 5, sf::Vector2u(578, 1), sf::Vector2u(84, 19), true);
	getSection("enemy_dissolve_left")->setNextFrameFunction(rightToLeftFunction);
	sectionMap["enemy_walk_out"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(492, 249), sf::Vector2u(618, 305), false);
	sectionMap["enemy_walk_out"] = new Section(textureMap[ENEMY],
		4, 1, sf::Vector2u(492, 249), sf::Vector2u(618, 305), false);




	//doors
	sectionMap["door_open"] = new Section(textureMap[DOOR],
		4, 1, sf::Vector2u(24, 2), sf::Vector2u(222, 62));
	sectionMap["door_close"] = new Section(textureMap[DOOR],
		4, 1, sf::Vector2u(24, 2), sf::Vector2u(222, 62));

	getSection("door_close")->setNextFrameFunction(rightToLeftFunction);
	//rails
	sectionMap["Rail"] = new Section(textureMap[RAIL],
		3, 1, sf::Vector2u(0, 0), sf::Vector2u(1000, 300));

	//bullet
	sectionMap["bullet_left"] = new Section(textureMap[BULLET],
		3, 1, sf::Vector2u(0, 0), sf::Vector2u(111, 35));
	sectionMap["bullet_right"] = new Section(textureMap[BULLET],
		3, 1, sf::Vector2u(141, 0), sf::Vector2u(247, 35));

}


void AnimationData::reloadTextures()
{
	textureMap[ENEMY]->loadFromFile("res/SpriteSheets/EnemyRemake.png");
	textureMap[ENEMY2]->loadFromFile("res/SpriteSheets/Enemy.png");
	textureMap[ENEMY3]->loadFromFile("res/SpriteSheets/Enemy_flipped.png");
	textureMap[ALBATROSS]->loadFromFile("res/SpriteSheets/Albatross.png");
	textureMap[DOOR]->loadFromFile("res/SpriteSheets/Door(1).png");
	textureMap[RAIL]->loadFromFile("res/SpriteSheets/RailFinal.png");
	textureMap[BULLET]->loadFromFile("res/SpriteSheets/bullet.png");
	textureMap[NAMCO]->loadFromFile("res/SpriteSheets/namco.png");
}


//This deletes all of the data so no leak
void AnimationData::unload()
{
	for (std::pair<const TextureName, sf::Texture*> texture : textureMap)
		delete texture.second;
	for (std::pair<std::string, Section*> section : sectionMap)
		delete section.second;
}


//This returns a map of the section for the desired spriteSheet
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