#include "State.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	Hero* hero;
	Maps* map;
public:
	GameState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
