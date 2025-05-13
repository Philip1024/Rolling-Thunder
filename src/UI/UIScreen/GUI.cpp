#include "GUI.h"

#include <iostream>

#include "../../SpriteData/AnimationData.h"


GUI::GUI(unsigned int* creditRef)
	: background(sf::Sprite(introFrame)), redNamcoSymbol(*AnimationData::getTexture(AnimationData::NAMCO)),
		creditRef(creditRef)
{
	currentScreen = MAIN_MENU;
	currentIntroFrame = 0;
	/* Resolution is cooked:
	  screen: 1920x1080 or 288x244 or ~288x180
	  x: ~50 to ~238 to keep 4:3 resolution
	  y: starts at 16 ends at 180
	*/
	redNamcoSymbol.setScale({ 0.08f, 0.08f });
	redNamcoSymbol.setOrigin({ redNamcoSymbol.getLocalBounds().size.x / 2.f, 0 });
	redNamcoSymbol.setPosition({ 144, 134 });

	// static text
	textMap["p1UpS"] = new GameText("1UP");
	textMap["p2UpS"] = new GameText("2UP");
	textMap["highScoreS"] = new GameText("HIGH SCORE");
	textMap["toStartPushS"] = new GameText("TO START PUSH");
	textMap["select1InfoS"] = new GameText("ONLY 1 PLAYER'S BUTTON");
	textMap["namcoCopyrightS"] = new GameText("© 1986 NAMCO");
	textMap["namcoRightsS"] = new GameText("ALL RIGHTS RESERVED");
	textMap["creditS"] = new GameText("CREDIT  ");
	textMap["manLeftS"] = new GameText("MAN");
	textMap["manRightS"] = new GameText("MAN");
	textMap["lifeS"] = new GameText("LIFE");
	textMap["bulletS"] = new GameText("BULLET");
	textMap["timeS"] = new GameText("TIME");

	// dynamic text
	textMap["p1ScoreD"] = new GameText("00"); // right aligned
	textMap["p2ScoreD"] = new GameText("00"); // right aligned
	textMap["creditD"] = new GameText("0"); // cannot go over 9
	textMap["highScoreD"] = new GameText("30000");
	textMap["bulletD"] = new GameText("50");
	textMap["timeD"] = new GameText("150");

	for (auto& it : textMap)
	{
		it.second->setScale(sf::Vector2f(0.2f, 0.2f));
		it.second->setPosition(sf::Vector2f(50, 50));
	}

	// static text
	QSP("p1UpS", { 75, 0 });
	QSP("p2UpS", { 238 - 30, 0 });
	setCenterOrigin("highScoreS");
	QSP("highScoreS", { 153, 0 });
	setCenterOrigin("toStartPushS");
	QSP("toStartPushS", { 144, 74 });
	setCenterOrigin("select1InfoS");
	QSP("select1InfoS", { 144, 87 });
	setCenterOrigin("namcoCopyrightS");
	QSP("namcoCopyrightS", { 144, 114 });
	setCenterOrigin("namcoRightsS");
	QSP("namcoRightsS", { 144, 126 });
	QSP("creditS", { 50, 164 });
	QSP("manLeftS", {60, 28});
	QSP("manRightS", {238 - 20, 28});
	QSP("lifeS", {130, 170});
	QSP("bulletS", {105, 170});
	QSP("timeS", {200, 170});


	// dynamic text
	textMap["p1ScoreD"]->setOrigin({ textMap["p1ScoreD"]->getLocalBounds().size.x, 0 });
	QSP("p1ScoreD", {107, 6});
	textMap["p2ScoreD"]->setOrigin({ textMap["p2ScoreD"]->getLocalBounds().size.x, 0 });
	QSP("p2ScoreD", { 240, 6 });
	textMap["creditD"]->setOrigin({ textMap["creditD"]->getLocalBounds().size.x, 0 });
	QSP("creditD", { 105, 164 });

}


GUI::~GUI()
{
	
}


/// <summary>
/// Renders the current GUI based on the currentScreen. Call in Game
/// </summary>
/// <param name="window"></param>
void GUI::drawGUI(sf::RenderWindow& window)
{
	static std::vector<std::string> textToDrawS1 = // we make static so we aren't create copies of this each tick
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
	static std::vector<std::string> textToDrawIngame = // we make static so we aren't create copies of this each tick
	{
		"p1UpS",
		"p2UpS",
		"highScoreS",
		"manLeftS",
		"manRightS",
		"bulletS",
		"lifeS",
		"timeS",
		"p1ScoreD",
		"p2ScoreD",
		"highScoreD",
		"bulletD",
		"timeD"
	};
	sf::RectangleShape alignLineX, alignLineY;
	textMap["creditD"]->setString(std::string(1, '0' + *creditRef));

	switch (currentScreen)
	{
	case MAIN_MENU:
		nextIntroFrame();
		window.draw(background);
		// TODO on frame 1050: show high score screen
		break;
	case SELECT_1:
		for (std::string& s : textToDrawS1)
			window.draw(*textMap[s]);
		window.draw(redNamcoSymbol);
		break;
	case SELECT_12:
		break;
	case INGAME:
		for (std::string& s : textToDrawIngame)
			window.draw(*textMap[s]);
		break;
	case START_TIMER:
		break;
	case GAME_OVER:
		break;
	case CONTINUE_TIMER:
		break;
	}

	alignLineX.setSize({ 188, 1 });
	alignLineX.setPosition({ 50, 90 });
	alignLineX.setFillColor(sf::Color::White);

	alignLineY.setSize({ 1, (float)window.getSize().y });
	alignLineY.setPosition({ 144, 0 });
	alignLineY.setFillColor(sf::Color::White);
	//window.draw(alignLineX); // TODO Ndebug this
	//window.draw(alignLineY);
}

/// <summary>
/// Advances the frame for the intro by one.
/// </summary>
void GUI::nextIntroFrame()
{
	currentIntroFrame %= 1240;
	currentIntroFrame++;
	if (!introFrame.loadFromFile("res/frames/frame_" + frameNumber(currentIntroFrame) + ".jpg"))
		throw std::exception("Unable to load frame.");
	background.setTexture(introFrame);
	background.setTextureRect({{ 0,0 }, { 1920, 1080 }});
	background.setOrigin({ 1920 / 2.f, 1080 / 2.f });
	background.setPosition({ 288/2.f,85 });
	background.setScale({0.13f, 0.159f }); 
}


/// <summary>
/// Sets the center origin to {middleX, 0}.
/// </summary>
/// <param name="textS">The string referring to the text to change.</param>
void GUI::setCenterOrigin(std::string textS)
{
	GameText* text = textMap[textS];
	text->setOrigin({ text->getLocalBounds().size.x / 2.f, 0 });
}


/// <summary>
/// Sets the position of the text referred to by the string at position v
/// </summary>
/// <param name="s"></param>
/// <param name="v">Define using {x, y}</param>
void GUI::QSP(std::string s, sf::Vector2f v)
{
	textMap[s]->setPosition(v);
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
