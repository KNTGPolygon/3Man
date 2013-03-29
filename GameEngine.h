#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Maps.h"
#include "Button.h"
#include "Functions.h"
#include "MapCreator.h"


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
	bool fpsFlag;
	
	float lastTime;
	float currentTime;
	Button *gameStart;
	Button *mapEditor;

	sf::Event event;
	sf::RenderWindow window; 
	sf::View View;
	
	sf::Sprite spr;
	sf::Vector2f vect;
	sf::Clock time;

	const sf::Vector2f *ptrToVect;
	const sf::Input & steering ;
	
	sf::String strMouse;
	sf::String strFps;
	sf::String strFrameTime;

	void EventHandling();
	void Display();

	Hero *hero;
	Maps *map;
	MapCreator *mapCreator;
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