#pragma once
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
class Animate
{
private:
	sf::Image myTexture;
	sf::Sprite *mySprite;
	sf::Clock time;
	int frameRate;
	int frameNumber;
	int numberOfFrames;
public:

	Animate(std::string filePath,sf::Vector2i FrameSize,sf::Vector2f Position,int NumberOfFrames,int FrameRate,int Shift = 0);
	~Animate(void);

	void Update(sf::Vector2f Position);
	void Display(sf::RenderWindow *window);
};
