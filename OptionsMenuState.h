#include "State.h"
#include "Button.h"
#include "InputBox.h"
#include "TextBox.h"

#ifndef OPTIONSMENUSTATE_H
#define OPTIONSMENUSTATE_H

class OptionsMenuState : public State
{
private:
	Button* music;
	Button* sounds;
	Button* mainMenu;
	TextBox* musicTextBox;
	TextBox* soundTextBox;
	Button* fullscreen;
	TextBox* fullscreenTextBox;
	sf::Sprite title;
	sf::String info;

public:
	OptionsMenuState();
	void Init();
	void Display();
	void UpdateSystem();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif
