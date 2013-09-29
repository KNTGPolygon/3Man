#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.h"
#include "MapObject.h"


#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

enum CreatorStates {SET_MAP_SIZE, MAIN};
enum ToolboxMenuState {SUBMENU_CHOICE, GROUNDS, OBJECTS, ENEMIES};

class MapCreator{

private:
	unsigned int Size;
	unsigned int toolboxFirstFieldNumber;
	bool lControlPressed;

	ToolboxMenuState toolboxMenuState;
	int hotKeys[10];
	int chosenTileFromToolbox;
	int chosenObjectFromToolbox;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	sf::Vector2f cameraPosition;

	std::map <int, sf::Image> tileGraphics;
	std::vector <sf::Sprite> tileSprites;

	std::map <int, sf::Image> objectGraphics;
	std::vector <sf::Sprite> objectSprites;

	int whichSubmenuButtonAnimate;
	sf::Image submenuButtonImage [6];
	sf::Sprite *submenuButtonSprite [6];
	//rectangles for main toolbox-menu
	sf::IntRect submenuButtonRectangles [4];
	//rectangle for return-button in submenus
	sf::IntRect submenuReturnButtonRectangle;

	 Tile ** createdMap;
	 MapObject ** mapObjects;

	 sf::Shape blackBackgroundShape;

	 sf::Vector2i noOfTilesVisible;

	std::map <int, sf::IntRect> toolboxRectangles;

	const sf::Input &steering;

public:
	MapCreator(const sf::Input &_steering);
	void Run();
	bool LoadTileGraphics();

	void Display(sf::RenderWindow *window);

	void CreateSprites();
	void toolboxManagement(sf::Vector2i toolboxClickPosition);
	void changingSpriteInMap(sf::Vector2i mapClickPosition);
	void changingObjectInMap(sf::Vector2i mapClickPosition);

	void initializeMapArrays (unsigned int Size);

	void GetSteeringEvent();
	void GetEvent(sf::Event&);
	void GetTextboxEvent(sf::Event&, std::string text, CreatorStates &state);

	void MoveCamera(sf::View *View, sf::RenderWindow *window);
	void GetScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);

	bool saveMap (std::string filename);

	~MapCreator();

};

#endif
