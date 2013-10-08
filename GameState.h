#include "State.h"
#include "Hero.h"
#include "Maps.h"
#include "Levels/Wall.h"
#include "Enemy.h"
#include "Number.h"
#include "Collision/QuadtreeNode.h"
#include "Enemies/PathFinder.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	int counter;
	int path;
	sf::Vector2i lastPath[2];
	std::vector<Drawable*> DrawableEntityList;
	Hero* hero;
	Maps* map;

	Enemy* pirate;

	int iterator;
	int mapPixelatedSize;
	int numberOfObjects;
	GameObject ** arrayOfObjects;
	static const int NUM_OF_ENEMIES = 5;
public:
	GameState();
	void Init();
	void Display();
	void UpdateSystem();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
