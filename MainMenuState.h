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
	sf::Sprite title;
	sf::String info;

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
