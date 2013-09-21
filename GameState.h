#include "State.h"
#include "Hero.h"
#include "Maps.h"
#include "Levels/Wall.h"
#include "Enemy.h"
#include "Number.h"
#include "Collision/QuadtreeNode.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	Hero* hero;
	Maps* map;
	Wall* wall[10];
	Enemy* pirate;
	Number *seven;
	Number **numbers;

	int mapPixelatedSize;
	int numberOfObjects;
	GameObject ** arrayOfObjects;
	static const int NUM_OF_ENEMIES = 5;
public:
	GameState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
