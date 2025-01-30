#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// This class stores the data needed for entities' animations.
/// Split into sections: named with what the purpose is
///
/// Sections include:
/// - name
/// - the texture*
/// - horizontal: how many frames on the x axis
/// - vertical: how many frames on the y axis
/// - vec2i start (top left)
/// - vec2i end (bottom right)
///
/// Based on this info, it will automatically split the section into frames.
/// TextureData is a collection of sections for specific entities.
/// </summary>
class TextureData
{
public:
	class Section
	{
	public:
		Section(std::string name, sf::Texture* texture, unsigned int horizontalFrames,
			unsigned int verticalFrames, sf::Vector2i start, sf::Vector2i end)
			:	name(name), texture(texture), horizontalFrames(horizontalFrames),
				verticalFrames(verticalFrames), start(start), end(end)
		{
			
		}
	private:
		std::string name;
		sf::Texture* texture;
		unsigned int horizontalFrames, verticalFrames;
		sf::Vector2i start, end;
	};
	Section getSection(std::string section);
private:
	std::vector<Section> sections;
};
