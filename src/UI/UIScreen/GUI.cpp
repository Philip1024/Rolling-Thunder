#include "GUI.h"


GUI::GUI()
	: background(sf::Sprite(introFrame))
{
	currentScreen = MAIN_MENU;
	currentIntroFrame = 0;
}


GUI::~GUI()
{
	
}


void GUI::drawGUI(sf::RenderWindow& window)
{
	switch (currentScreen)
	{
	case MAIN_MENU:
		// play the video etc. TODO
		nextIntroFrame();
		window.draw(background);
		break;
	case SELECT_1:
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
