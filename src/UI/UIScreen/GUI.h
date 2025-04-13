#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "../GameText/GameText.h"


/// <summary>
/// This class controls the GUI of the game.
///
/// Trey: record a video of the opening sequence. do not run the game in fullscreen as it scales and anti aliases the game.
/// use obs or whatever other program you know. Record in the resolution the game runs (do not scale!), and in 30fps.
/// Edit the video to remove the leaderboard in the frames that ha ve it, and replace it with the blue color that's there.
/// You could also edit the frames themselves if it would be easier than the video.
/// Convert the video to frames (images) and make a folder for the frames and upload to github: https://ezgif.com/video-to-jpg
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
	Screen currentScreen;
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