#include "State.h"
#include "Hero.h"
#include "Maps.h"
#include "Tree.h"
#include "Enemy.h"
#include "Collision/QuadtreeNode.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	Hero* hero;
	Maps* map;
	Tree* tree[20];
	Enemy* pirate;

	int numberOfObjects;
	GameObject ** arrayOfObjects;

public:
	GameState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
