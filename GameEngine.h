#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include "Singleton.h"
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
#include "Enemies/PathFinder.h"

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

class GameEngine : public Singleton<GameEngine>
{
public:	
	static const int SCREEN_WIDTH  = 800;
	static const int SCREEN_HEIGHT = 600;
	bool devmode;
	PathFinder *pathfinder;
private:

	bool sounds;
	bool windowIsOpen;
	bool mainMenu;
	bool fpsFlag;
	
	int **mapObjectsGrid;
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
	
	std::vector<sf::Vector3i> objectsList;
	sf::Vector2i objectGridSize;
	sf::SoundBuffer soundBuffer;
	sf::Music soundtrack;

	void Display();

public:
	bool run(void);

	GameEngine(void);
	~GameEngine(void);
		
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
	sf::Clock& GetTimer();
	void SetSounds(bool);
	bool Sounds();

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
	void SetMapObjectsGrid( std::vector<sf::Vector3i> objects , int gridSize );
	int GetPointWeight( sf::Vector3i point);
	sf::Vector2f GetMouseCoords();
	std::vector<sf::Vector3i> GetObjects();
	sf::Vector2i GetGridSize();

};


void deleteObj(void *obj);
#endif
