#pragma once
#include <SFML/Graphics.hpp>


/// <summary>
/// This is different from sf Text because it has some default changes.
/// </summary>
class GameText : public sf::Text
{
public:
	GameText(std::string text);
private:
	static sf::Font gameFont;
};