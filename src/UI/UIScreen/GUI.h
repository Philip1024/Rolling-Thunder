#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "../GameText/GameText.h"


/// <summary>
/// This class controls the GUI of the game.
///
/// 
/// For the main menu: make a recording until the player presses 5, where we will switch to ingame animation.
/// For the leaderboard, we can edit the video and replace the included leaderboard with the blue color, then add in our own during those certain frames.
/// </summary>
class GUI
{
public:
	enum Screen;

	// create once in Game.cpp
	GUI();
	~GUI();

	// draws the current screen
	void drawGUI(sf::RenderWindow& window);
	
	void changeScreen(Screen s) { this->currentScreen = s; }
private:
	// converts an int to a usuable string for the frames
	static std::string frameNumber(unsigned int i);
	// advances to the next frame in the intro video
	void nextIntroFrame();

	sf::Texture introFrame;
	unsigned int currentIntroFrame;

	Screen currentScreen;
	sf::Sprite background;
	std::unordered_map<std::string, GameText*> textMap;
};


enum GUI::Screen
{
	MAIN_MENU,
	SELECT_1,
	SELECT_12, // includes the text for both players
	INGAME,
	START_TIMER,
	GAME_OVER,
	CONTINUE_TIMER,
};


