#include "GUI.h"


GUI::GUI()
{
	currentScreen = MAIN_MENU;
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