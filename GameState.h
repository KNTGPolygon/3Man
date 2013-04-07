#include "State.h"
#include "Hero.h"
#include "Maps.h"
#include "Tree.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	Hero* hero;
	Maps* map;
	Tree* tree[8];
public:
	GameState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
