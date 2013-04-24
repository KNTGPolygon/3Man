#include "State.h"
#include "Hero.h"
#include "Maps.h"
#include "Tree.h"
#include "Enemy.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	Hero* hero;
	Maps* map;
	Tree* tree[20];
	Enemy* pirate;

public:
	GameState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
