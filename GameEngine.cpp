#include "GameEngine.h"

GameEngine::GameEngine(void):steering(window.GetInput())
{
	window.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "3Game");
}

GameEngine::~GameEngine(void)
{
	//freeResources(); ale to potem 
	window.Clear();
	window.Close();
}
void GameEngine::EventHandling()
{
		while(window.GetEvent(event))
		{
			if(event.Type==sf::Event::Closed)
			{
				window.Close();
			}
		}
		 		
}
void GameEngine::Display()
{
		 window.Clear( sf::Color( 0, 0, 0 ) );
		 window.Display();
}
bool GameEngine::run()
{
	bool windowIsOpen = window.IsOpened();
	window.SetFramerateLimit(100);
	window.Clear();

	while (windowIsOpen)
	{
	EventHandling();
	Display();
	}
	return 0;
}
void deleteObj(void *obj)
{
	if (obj != NULL)
	{
		delete obj;
		obj = NULL;
	}
}

GameEngine* GameEngine::engine = NULL;
GameEngine* GameEngine::getInstance(void)
{
	if(engine == NULL)	
	{
		engine = new GameEngine();
	}
	return engine;
}
