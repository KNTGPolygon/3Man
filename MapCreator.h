#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.h"
#include "MapObject.h"


#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

class MapCreator{

private:
	//how many fields does the createdMap have
	//toolboxFirstFieldNumber is used in browsing through toolbox fields
	int Size;
	int toolboxFirstFieldNumber;
	int verticalToolboxFirstFieldNumber;

	int chosenTileFromToolbox;
	int chosenObjectFromToolbox;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	sf::Vector2f cameraPosition;

	std::map <int, sf::Image> tileGraphics;
	std::vector <sf::Sprite> tileSprites;

	std::map <int, sf::Image> objectGraphics;
	std::vector <sf::Sprite> objectSprites;

	 Tile ** createdMap;
	 MapObject ** map_data;

	 sf::Image *blackHorizontalImage;
	 sf::Sprite *blackHorizontalSprite;
	 sf::Image *blackVerticalImage;
	 sf::Sprite *blackVerticalSprite;

	 sf::Vector2f sampleSpriteSize;
	 sf::Vector2i noOfTilesVisible;

	std::map <int, sf::IntRect> toolboxRectangles;
	std::map <int, sf::IntRect> toolboxVerticalRectangles;

	const sf::Input &steering;

public:
	MapCreator(const sf::Input &_steering);
	void Run();
	void LoadTileGraphics();
	void Display(sf::RenderWindow *window);
	void CreateSprites();
	void toolboxManagement(sf::Vector2i toolboxClickPosition);
	void changingSpriteInMap(sf::Vector2i mapClickPosition);

	void GetSteeringEvent();
	void GetEvent(sf::Event&);

	void MoveCamera(sf::View *View, sf::RenderWindow *window);
	void GetScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);

};

#endif
