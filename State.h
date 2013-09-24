#include "GameEngine.h"

#ifndef STATE_H
#define STATE_H

class State
{
protected:
	bool init;
public:
	State();
	virtual ~State();
	virtual void Init() = 0;
	virtual void Display() = 0;
	virtual void UpdateSystem() = 0;
	virtual void EventHandling() = 0;
	virtual void GetEvents() = 0;
	virtual void Cleanup() = 0;
	bool Initialized();
};

#endif
