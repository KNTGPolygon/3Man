#include "GameEngine.h"

GameEngine::GameEngine(void):steering(window.GetInput())
{	
	window.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "3Game");
	//View.SetHalfSize((float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT/2); 
	//window.SetView(View);
	mainMenu = true;
	map = new Maps("Data/Maps/Test.map");
	mapEditor = new Button(steering,sf::Vector2f((float)(SCREEN_WIDTH/2 -50.0), (float)SCREEN_HEIGHT/2),sf::Vector2f(100.0,50.0),sf::Color(125,125,125),"Edytor");
	gameStart = new Button(steering,sf::Vector2f((float)(SCREEN_WIDTH/2 -50.0), (float)(SCREEN_HEIGHT/2 - 100.0)),sf::Vector2f(100.0,50.0),sf::Color(125,125,125),"Gra");
	
	hero = new Hero(steering,2);
	hero->PutScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	strMouse.SetPosition(10.0,150.0);
	strMouse.SetScale(0.5,0.5);
	strMouse.SetText("Pozycja myszki");
		
	//!!created map editor!!
	mapCreator = new MapCreator(steering);
	mapCreator->GetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	windowIsOpen = window.IsOpened();
}

GameEngine::~GameEngine(void)
{
	//freeResources(); ale to potem 
	window.Clear();
	window.Close();
}
void GameEngine::EventHandling()
{
	if(gameStart->pressed == true )
	{
	hero->UpdatePosition();
	hero->GetEvent();
	}

	if(mainMenu == true)
	{
		window.SetView(window.GetDefaultView());
		
		gameStart->GetEvent();
		mapEditor->GetEvent();
	}

	if(mapEditor->pressed == true)
	{
		mapCreator->GetSteeringEvent();
			// Tu mstanki2 piszesz co ma pobierac za eventy(steering)
			// lub nizej w while
	}
		while(window.GetEvent(event))
		{
			if(event.Type==sf::Event::Closed)
			{
				window.Close();
			}
			 if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
			{
				mainMenu = true;
				gameStart->pressed = false;
				mapEditor->pressed = false;
			}

			 //it's here cause I need direct access to window events
			 mapCreator->GetEvent(event);
		}
		 		
}
void GameEngine::Display()
{
	    window.Clear( sf::Color( 0, 0, 0 ) );
		
		strMouse.SetText("X = "+int2str(steering.GetMouseX())+" Y = "+int2str(steering.GetMouseY()));
		window.Draw( strMouse);

		if(mainMenu == true)
		{
		mapEditor->Display(&window);
		gameStart->Display(&window);
		
		}

		if(gameStart->pressed == true )
		{
			mainMenu = false;
		 map->showMap(&window);
		 hero->SetCamera(&View,&window);
		 hero->Display(&window);
		}
		if(mapEditor->pressed == true)
		{
			mainMenu = false;
			mapCreator->MoveCamera(&View, &window);
			mapCreator->Display(&window);
			window.Draw( strMouse);
			// Tu mstanki2 piszesz co ma wyswietlac ten edytor
		}
		 window.Display();
}

bool GameEngine::run()
{
	window.SetFramerateLimit(100);
	window.Clear();
	//map->showMap();

		while (windowIsOpen)
		{
		EventHandling();
		Display();
		sf::Sleep(0.05);

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
