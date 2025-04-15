#include "GameText.h"
sf::Font GameText::gameFont = sf::Font("res/namco-arcade-raster/namco-arcade-raster.ttf");


GameText::GameText(std::string text)
	: sf::Text(gameFont)
{
	setString(text);
	setFillColor(sf::Color::White);
}
