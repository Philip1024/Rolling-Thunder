#include "GUI.h"

#include <iostream>


GUI::GUI()
	: background(sf::Sprite(introFrame))
{
	currentScreen = MAIN_MENU;
	currentIntroFrame = 0;
	// screen: 1920x1080 or 288x244 or ~288x180

	// static text
	textMap["p1UpS"] = new GameText("1UP");
	textMap["p2UpS"] = new GameText("2UP");
	textMap["highScoreS"] = new GameText("HIGH SCORE");
	textMap["toStartPushS"] = new GameText("TO START PUSH");
	textMap["select1InfoS"] = new GameText("ONLY 1 PLAYER'S BUTTON");
	textMap["namcoCopyrightS"] = new GameText("@ 1986 NAMCO");
	textMap["namcoRightsS"] = new GameText("ALL RIGHTS RESERVED");
	textMap["creditS"] = new GameText("CREDIT  ");

	// dynamic text
	textMap["p1ScoreD"] = new GameText("00");
	textMap["p2ScoreD"] = new GameText("00");
	textMap["creditD"] = new GameText("1");

	for (auto& it : textMap)
	{
		it.second->setScale(sf::Vector2f(0.2f, 0.2f));
		it.second->setPosition(sf::Vector2f(50, 50));
	}

	textMap["creditS"]->setPosition(sf::Vector2f(0, 170));

}


GUI::~GUI()
{
	
}


void GUI::drawGUI(sf::RenderWindow& window)
{
	static std::vector<std::string> textToDraw = // we make static so we aren't create copies of this each tick
	{
	"p1UpS",
	"p2UpS",
	"highScoreS",
	"toStartPushS",
	"select1InfoS",
	"namcoCopyrightS",
	"namcoRightsS",
	"creditS",
	"p1ScoreD",
	"p2ScoreD",
	"creditD"
	};

	switch (currentScreen)
	{
	case MAIN_MENU:
		// play the video etc. TODO
		nextIntroFrame();
		window.draw(background);
		// 1050: high score
		break;
	case SELECT_1:
		

		for (std::string& s : textToDraw)
			window.draw(*textMap[s]);
		break;
	case SELECT_12:
		break;
	case INGAME:
		break;
	case START_TIMER:
		break;
	case GAME_OVER:
		break;
	case CONTINUE_TIMER:
		break;
	}
}

void GUI::nextIntroFrame()
{
	currentIntroFrame %= 1240;
	currentIntroFrame++;
	if (!introFrame.loadFromFile("res/frames/frame_" + frameNumber(currentIntroFrame) + ".jpg"))
		throw std::exception("Unable to load frame.");
	background.setTexture(introFrame);
	background.setTextureRect({{ 0,0 }, { 1920, 1080 }});
	background.setPosition({ 0,16.5f });
	background.setScale({0.1489f, 0.1489f }); 
}

std::string GUI::frameNumber(unsigned int i)
{
	unsigned int length = log10(i) + 1;
	std::string prefix;

	switch (length)
	{
	case 1:
		prefix = "000";
		break;
	case 2:
		prefix = "00";
		break;
	case 3:
		prefix = "0";
		break;
	case 4:
		prefix = "";
		break;
	default:
		throw std::invalid_argument("i (frame number) is not in range: 1-9999");
	}

	return prefix + std::to_string(i);
}
