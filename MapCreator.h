#pragma once

#include <iostream>
#include "Tile.h"
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>


#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

enum MapEditorStates {CHOOSING_ARRAY};

class MapCreator{

private:
	//how many fields does the createdMap have
	//cooldown used in events (delay after pressing a button)
	//toolboxFirstFieldNumber is used in browsing through toolbox fields
	int Size;
	double cooldown;
	int toolboxFirstFieldNumber;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	sf::Vector2f cameraPosition;

	MapEditorStates state;

	std::map <int, Tile> tileGraphics;
	std::vector <sf::Sprite> tileSprites;

	 Tile ** createdMap;
	 sf::Image *blackImage;
	 sf::Sprite *blackSprite;
	 sf::Vector2f sampleSpriteSize;
	 sf::Vector2i noOfTilesVisible;


	const sf::Input &steering;
	sf::Clock clock;

public:
	MapCreator(const sf::Input &_steering);
	void Run();
	void LoadTileGraphics();
	void Display(sf::RenderWindow *window);
	void CreateSprites();

	void GetSteeringEvent();
	void GetEvent(sf::Event);

	void MoveCamera(sf::View *View, sf::RenderWindow *window);
	void GetScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);

};

#endif