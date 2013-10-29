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
	bool lShiftPressed;

	ToolboxMenuState toolboxMenuState;
	int hotKeys[10];
	int chosenTileFromToolbox;
	int chosenObjectFromToolbox;
	int chosenEnemyFromToolbox;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	sf::Vector2f cameraPosition;

	std::map <int, sf::Image> tileGraphics;
	std::vector <sf::Sprite> tileSprites;

	std::map <int, sf::Image> objectGraphics;
	std::vector <sf::Sprite> objectSprites;

	std::map <int, sf::Image> enemyGraphics;
	std::vector <sf::Sprite> enemySprites;

	int whichSubmenuButtonAnimate;
	sf::Image submenuButtonImage [6];
	sf::Sprite *submenuButtonSprite [6];
	//rectangles for main toolbox-menu
	sf::IntRect submenuButtonRectangles [4];
	//rectangle for return-button in submenus
	sf::IntRect submenuReturnButtonRectangle;

	 Tile ** createdMap;
	 MapObject ** mapObjects;
	 int ** arrayOfEnemies;

	 sf::Shape blackBackgroundShape;

	 sf::Vector2i noOfTilesVisible;

	std::map <int, sf::IntRect> toolboxRectangles;

	const sf::Input &steering;

	void saveMapToFile (std::string filename);
	void saveMap_SavingUsedObjectsNamesPhase(std::ifstream& editorLoadingFile_inputStream, std::ofstream& outputFileStream);
	void saveMap_SavingGroundTilesPhase(std::ofstream& outputFileStream);
	void saveMap_SavingObjectsPhase(std::ofstream& outputFileStream);
	void saveMap_SavingEnemiesPhase(std::ofstream& outputFileStream);

	void LoadMapFromFile (const std::string& filename);
	void LoadMap_LoadSize(std::ifstream &inputFileStream);
	void LoadMap_SkipTileAndObjectNames(std::ifstream &inputFileStream);
	void LoadMap_LoadGroundTiles(std::ifstream &inputFileStream);
	void LoadMap_LoadObjects(std::ifstream &inputFileStream);
	void LoadMap_LoadEnemies(std::ifstream &inputFileStream);

public:
	MapCreator(const sf::Input &_steering);
	void Run();
	bool LoadTileGraphics();

	void Display(sf::RenderWindow *window);

	void CreateSprites();
	void toolboxManagement(sf::Vector2i toolboxClickPosition);

	bool isChosenEnemyFieldFreeOfObjects(sf::Vector2i enemy_inEnemyArrayPosition);
	bool isChosenObjectFieldFreeOfEnemies(sf::Vector2i object_inObjectArrayPosition);
	void changingSpriteInMap(sf::Vector2i mapClickPosition);
	void changingObjectInMap(sf::Vector2i mapClickPosition);
	void changingEnemyInMap(sf::Vector2i mapClickPosition);

	void InitializeMapCreatorArrays (unsigned int Size);
	void DestroyMapCreatorArrays (unsigned int Size);

	void GetSteeringEvent();
	void GetEvent(sf::Event&);
	void GetTextboxEvent(sf::Event&, std::string text, CreatorStates &state);

	void MoveCamera(sf::View *View, sf::RenderWindow *window);
	void GetScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);


	~MapCreator();

};

#endif
