#include "State.h"
#include "MapCreator.h"
#include "InputBox.h"
#include "TextBox.h"

#ifndef EDITORSTATE_H
#define EDITORSTATE_H


class EditorState : public State
{

private:
	MapCreator *mapCreator;
	InputBox* inputBox;
	TextBox * textBox;
	CreatorStates state;
	
public:
	EditorState();
	void Init();
	void Display();
	void UpdateSystem();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
