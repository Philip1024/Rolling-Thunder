#pragma once
#include <SFML/Graphics.hpp>
#include "../Entity/Player/Player.h"
#include "../SpriteData/AnimationData.h"


class Game
{
public:
	Game();
	~Game();
	void run();
	void isColliding();
	Player* player;
	sf::Texture stage1;
	sf::Texture stage2;
	sf::Texture stage3;
	sf::Texture stage4;
	sf::Texture stage5;
};

