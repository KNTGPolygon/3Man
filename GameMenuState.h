#include "State.h"
#include "Button.h"
#include "InputBox.h"
#include "TextBox.h"

#ifndef GAMEMENUSTATE_H
#define GAMEMENUSTATE_H

class GameMenuState : public State
{
private:
	Button* gameStart;
	Button* exit;
	Button* userGameStart;
	sf::Sprite title;
	sf::String info;


public:
	GameMenuState();
	void Init();
	void Display();
	void UpdateSystem();
	void EventHandling();
	void GetEvents();
	void Cleanup();
};

#endif


