#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
class GameEngine
{
public:	
	static const int SCREEN_WIDTH  = 800;
	static const int SCREEN_HEIGHT = 600;
private:
	sf::Event event;
	sf::RenderWindow window; 

	const sf::Input & steering ;

	void EventHandling();
	void Display();

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