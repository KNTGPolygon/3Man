#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Maps.h"
#include "Button.h"
#include "Functions.h"

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
class GameEngine
{
public:	
	static const int SCREEN_WIDTH  = 800;
	static const int SCREEN_HEIGHT = 600;
private:

	bool windowIsOpen;
	bool mainMenu;

	Button *gameStart;
	Button *mapEditor;

	sf::Event event;
	sf::RenderWindow window; 
	sf::View View;
	const sf::Input & steering ;
	
	sf::String strMouse;

	void EventHandling();
	void Display();

	Hero *hero;
	Maps *map;
public:
	bool run(void);

	GameEngine(void);
	~GameEngine(void);
		static GameEngine* getInstance(void);

private:
		static GameEngine * engine;
};

void deleteObj(void *obj);
#endif