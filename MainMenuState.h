#include "State.h"
#include "Button.h"
#include "InputBox.h"

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

class MainMenuState : public State
{
private:
	Button* gameStart;
	Button* mapEditor;
	Button* exit;
	InputBox* inputBox;

public:
	MainMenuState();
	void Init();
	void Display();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
