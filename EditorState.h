#include "State.h"
#include "MapCreator.h"

#ifndef EDITORSTATE_H
#define EDITORSTATE_H

class EditorState : public State
{
private:
	MapCreator *mapCreator;
public:
	EditorState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
