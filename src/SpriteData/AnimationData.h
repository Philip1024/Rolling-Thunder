#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

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
/// AnimationData is a collection of sections for specific entities.
///
/// Why are we doing this? Many of the frames in the spritesheets are spaced differently. Each section has consistent spacing.
/// It also allows us to split them up by their action, such as "MoveLeft" or "Die"
/// </summary>
class AnimationData
{
public:
	enum TextureName;
	class Section;

	// EXPECTED TO BE CALLED
	static void load();
	static void unload();

	static Section getSection(std::string sectionName);
private:
	static std::string toLowerCase(std::string i);

	static std::unordered_map<std::string, Section> sectionMap;
	static std::unordered_map<TextureName, sf::Texture*> textureMap;
};

enum AnimationData::TextureName
{
	ENEMY,
	ALBATROSS,
	DOOR
};

// interior class to AnimationData
class AnimationData::Section
{
public:
	Section(std::string name, sf::Texture* texture, unsigned int horizontalFrames,
		unsigned int verticalFrames, sf::Vector2i start, sf::Vector2i end)
		: name(name), texture(texture), horizontalFrames(horizontalFrames),
		verticalFrames(verticalFrames), start(start), end(end)
	{

	}
private:
	std::string name;
	sf::Texture* texture;
	unsigned int horizontalFrames, verticalFrames;
	sf::Vector2i start, end;
};