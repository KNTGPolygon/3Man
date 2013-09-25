#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include "Cursor.h"
#include "Drawable.h"
#include "Util.h"
#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "OptionsMenuState.h"
#include "EditorState.h"
#include "SpriteExt.h"
#include "Collision/BoxMask.h"


#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

enum STATE { MAINMENU, OPTIONSMENU, EDITOR, GAME, NOSTATE };

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
	bool devmode;
private:

	bool windowIsOpen;
	bool mainMenu;
	bool fpsFlag;
	
	float lastTime;
	float currentTime;

	sf::Event event;
	sf::RenderWindow window; 
	sf::View View;

	Cursor cursor;
	
	std::map<STATE, State*> States;
	STATE currentState;
	STATE nextState;
	
	std::priority_queue<Drawable*, std::vector<Drawable*>, CompareDrawable> RenderQueue;

	QuadtreeNode* collisionQuadtree;

	sf::Sprite spr;
	sf::Clock time;

	const sf::Input & steering ;
	
	sf::String strFps;

	sf::SoundBuffer soundBuffer;
	sf::Music soundtrack;

	void Display();

public:
	bool run(void);

	GameEngine(void);
	~GameEngine(void);
	static GameEngine* getInstance(void);
		
	void ChangeState(STATE); // wysyla zadanie zmiany state'a
	void SwitchState();		 // dokonuje faktycznej zamiany state'ow (nie ruszac, to sie robi samo!)
	State* getCurrentState();
	
	void SwitchWindowIsOpen(bool WindowIsOpen);
	void AddToRenderQueue(Drawable*);
	void FlushRenderQueue();
	void ExecuteRenderQueue();

	sf::RenderWindow& getWindow();
	sf::View& getView();
	const sf::Input& getSteering();
	sf::Event& getEvent();
	Cursor& getCursor();
	sf::Music& getMusic();
	void SetDefaultView(); // menusy oraz interfejs
	void SetGameView(); // mapa i elementy gry

	static bool Collision( SpriteExt*, SpriteExt* );
	void AddToCollisionQuadtree(SpriteExt*);
	bool DetectCollision(SpriteExt*);
	bool DetectCollision(SpriteExt*, std::string);
	void DetectCollision(SpriteExt*, std::vector<SpriteExt*>&);
	void DetectCollision(SpriteExt*, std::vector<SpriteExt*>&, std::string);
	void ClearCollisionQuadtree();
	void DisplayCollisionQuadtree();

	sf::Vector2f GetMouseCoords();

private:
	static GameEngine * engine;
};


void deleteObj(void *obj);
#endif
