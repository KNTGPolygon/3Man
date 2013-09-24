#include "State.h"
#include "Button.h"
#include "InputBox.h"
#include "TextBox.h"

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

class MainMenuState : public State
{
private:
	Button* gameStart;
	Button* mapEditor;
	Button* exit;
	Button* options;
	InputBox* inputBox;

public:
	MainMenuState();
	void Init();
	void Display();
	void UpdateSystem();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
