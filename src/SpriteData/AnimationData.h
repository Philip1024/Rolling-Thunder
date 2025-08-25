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
///
///	Note: Frames go from top-left to bottom-right or left to right if verticalFrames = 1
/// </summary>
class AnimationData
{
public:
	enum TextureName;
	class Section;
	class SectionData;

	// EXPECTED TO BE CALLED
	static void load();
	static void unload();

	static Section* getSection(std::string sectionName);
	static sf::Texture* getTexture(TextureName name) { return textureMap[name]; }
	static void reloadTextures();
private:
	static std::string toLowerCase(std::string i);

	static std::unordered_map<std::string, Section*> sectionMap;
	static std::unordered_map<TextureName, sf::Texture*> textureMap;
};

enum AnimationData::TextureName
{
	ENEMY,//remake
	ENEMY2,//original enemy sprite sheet, used for death animation
	ENEMY3,//enemy sprite sheet flipped
	ALBATROSS,
	DOOR,
	RAIL,
	BULLET,
	NAMCO,
	SIZE
};

// interior class to AnimationData
class AnimationData::Section
{
public:
	/// Sections are animation strips to provide data for animating other objects.
	/// 
	/// @param texture The reference to the texture for the section to use.
	/// @param horizontalFrames The amount of frames left to right.
	/// @param verticalFrames The amount of frames top to bottom.
	/// @param topLeft Top left corner of the animation strip.
	/// @param bottomRight Either the bottom right corner or the size of the animation.
	/// @param useSize If true, will use the size of the animations instead of the bottom right corner.
	Section(sf::Texture* texture, unsigned int horizontalFrames,
	        unsigned int verticalFrames, sf::Vector2u topLeft, sf::Vector2u bottomRight, bool useSize = false)
		: texture(texture), horizontalFrames(horizontalFrames),
		verticalFrames(verticalFrames)
	{
		sf::Vector2u end = useSize ? sf::Vector2u(topLeft.x + bottomRight.x * horizontalFrames, topLeft.y + bottomRight.y * verticalFrames) : bottomRight;
		start = topLeft;
		this->end = end;
		unsigned int xDiff = end.x - topLeft.x, yDiff = end.y - topLeft.y;
		xSize = xDiff / horizontalFrames;
		ySize = yDiff / verticalFrames;
		nextFrameFunc = [](unsigned int& curFrame, unsigned int maxFrames) -> void { // LAMBDA
			curFrame++;
			curFrame %= maxFrames; // if bigger, reset to 0
		};
	}

	// this updates the function called in nextFrame in the SectionData for an Entity. By default this simply does curFrame++ (and checks bounds)
	void setNextFrameFunction(void (*func)(unsigned int&, unsigned int)) { this->nextFrameFunc = func; }
	auto getNextFrameFunction() { return nextFrameFunc; }

	// the one with one int gets the frame from top left to bottom right
	sf::IntRect getFrame(unsigned int c) const;
	// this getFrame gets the frame with x indicating the left to right position, and the y indicating the top to bottom position.
	sf::IntRect getFrame(unsigned int x, unsigned int y) const;
	unsigned int getMaxFramesHorizontal() const { return horizontalFrames; }
	unsigned int getMaxFramesVertical() const { return verticalFrames; }
	unsigned int getMaxFrames() const { return horizontalFrames*verticalFrames; }
private:
	sf::Texture* texture;
	unsigned int horizontalFrames, verticalFrames;
	unsigned int xSize, ySize;
	sf::Vector2u start, end;

	// this is a function pointer. when called, curFrame and maxFrames from this object will be passed in.
	void (*nextFrameFunc)(unsigned int& curFrame, unsigned int maxFrames);
};


// what this does: track the current frame for the Section an Entity uses. This is to allow multiple Entities to use the same section.
// Entities need to track however many SectionDatas as they have animations, through which they can request the nextFrame for each sectiondata.
class AnimationData::SectionData
{
public:
	SectionData(Section* linkedSection)
		: linkedSection(linkedSection), curFrame(0)
	{
		
	}
	// this calls the nextFrameFunc then returns getFrame(curFrame);
	sf::IntRect nextFrame();

	unsigned int getCurFrame() { return curFrame; }
private:
	Section* linkedSection;
	unsigned int curFrame;
};