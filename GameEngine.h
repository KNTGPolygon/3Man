#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <vector>
#include "Drawable.h"
#include "Functions.h"
#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "EditorState.h"
#include "SpriteExt.h"
#include "Collision/BoxMask.h"


#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

enum STATE { MAINMENU, EDITOR, GAME, NOSTATE };

class CompareDrawable
{
public:
	bool operator()(Drawable* obj1, Drawable* obj2)
	{
		if ( obj1->getDepth() < obj2->getDepth() ) return true;
		else return false;
	}
};

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

	sf::Event event;
	sf::RenderWindow window; 
	sf::View View;
	
	std::map<STATE, State*> States;
	STATE currentState;
	STATE nextState;
	
	std::priority_queue<Drawable*, std::vector<Drawable*>, CompareDrawable> RenderQueue;

	sf::Sprite spr;
	sf::Vector2f vect;
	sf::Clock time;

	const sf::Vector2f *ptrToVect;
	const sf::Input & steering ;
	
	sf::String strMouse;
	sf::String strFps;
	sf::String strFrameTime;

	void Display();

public:
	bool run(void);

	GameEngine(void);
	~GameEngine(void);
	static GameEngine* getInstance(void);
		
	void ChangeState(STATE); // wysyla zadanie zmiany state'a
	void SwitchState();		 // dokonuje faktycznej zamiany state'ow (nie ruszac, to sie robi samo!)
	State* getCurrentState();
	
	void AddToRenderQueue(Drawable*);
	void FlushRenderQueue();
	void ExecuteRenderQueue();

	sf::RenderWindow& getWindow();
	sf::View& getView();
	const sf::Input& getSteering();
	sf::Event& getEvent();

	static bool Collision( SpriteExt&, SpriteExt& );

private:
	static GameEngine * engine;
};


void deleteObj(void *obj);
#endif
