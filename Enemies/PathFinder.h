#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class Cell
{
public:
	int openListID; // chyba nie potrzebne
	int walkability;
	int whichList;
	int GCost;
	int FCost;
	int HCost;
	sf::Vector2i parent;

};
class OpenList
{
	
public:
	int totalSize;
	int *IDList;
	int size;
	int *HCost;
	int *FCost;
	sf::Vector2i *pointCoords;
	OpenList( int gridXSize, int gridYSize );
	~OpenList(void );
	void AddPointToList( sf::Vector2i point, int newItemFcost );
	void AddNewFCostAndSort( int pointID, int newFCost );
	void EreseFromList(  int pointID );
	int GetLowestFCostPointID();
	int GetPointID( sf::Vector2i point );

};
class PathFinder
{
public:
	static enum PATH_STATE{NOTFINISHED = 0, NOTSTARTED = 0, UNWALKABLE = 0, WALKABLE = 1, FOUND = 1, NONEXISTENT = 2};
	bool loaded;
private:
	int gridXSize;
	int gridYSize;
	int gridCellSize;

	int openListMarker;
	int closedListMarker;

	int numberOfMobs;

	std::vector<int> pathStatus;
	std::vector<int> pathLength;

	sf::Vector2i **pathBank;
	sf::Vector2i start;
	sf::Vector2i target;

	Cell **cell;
	OpenList *openList;

	std::vector<sf::Vector2i> foundedCoords;
private:
	void ErasePointFromOpenList( int pointID );
	void SearchPointsArround( sf::Vector2i thisPoint );
	int SaveFoundedPath(int pathfinderID , sf::Vector2i starting );
	void Cleanup();
public:
	void Initialization( std::vector<sf::Vector3i> objectList,int _gridXSize, int _gridYSize );	
	int FindPath( int pathfinderID, sf::Vector2i _start, sf::Vector2i _target );
	int AddNewMobID();
	void SetNumberOfMobs( int _numberOfMobs );
	std::vector<sf::Vector2i> GetPath(int pathfinderID );



	PathFinder(void);
	~PathFinder(void);
};
