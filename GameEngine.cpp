#include "GameEngine.h"

GameEngine::GameEngine(void):steering(window.GetInput())
{	
	window.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "3Game");
	
	States[GAME] = new GameState();
	States[MAINMENU] = new MainMenuState();
	States[EDITOR] = new EditorState();
	currentState = NOSTATE;
	
	time.Reset();
	currentTime=0;
	lastTime = 0;
	mainMenu = true;
	fpsFlag = true;

	strMouse.SetPosition(10.0,150.0);
	strMouse.SetScale(0.5,0.5);
	strMouse.SetText("Pozycja myszki");
	strFps.SetPosition(10.0,50.0);
	strFps.SetScale(0.5,0.5);
	strFps.SetText("FPS : ");
	strFrameTime.SetPosition(10.0,100.0);
	strFrameTime.SetScale(0.5,0.5);
	strFrameTime.SetText("Frame time : ");

	windowIsOpen = window.IsOpened();
	
	ptrToVect = &spr.GetPosition(); // pointer na vector2f
	
}

GameEngine::~GameEngine(void)
{
	//freeResources(); ale to potem 
	window.Clear();
	window.Close();
}

void GameEngine::Display()
{
		strMouse.SetText("X = "+int2str(steering.GetMouseX())+" Y = "+int2str(steering.GetMouseY()));
		window.Draw( strMouse);
		
		if(fpsFlag == true)
		{
			currentTime = time.GetElapsedTime();	
			strFps.SetText("FPS = "+int2str((int)(1/(currentTime-lastTime))));
			strFrameTime.SetText("Frame time = "+flo2str(window.GetFrameTime()));
			window.Draw( strFps );
			window.Draw( strFrameTime );
			lastTime = currentTime;	
		}
}

void GameEngine::ChangeState( STATE state )
{
	if ( currentState != NOSTATE )
		getCurrentState()->Cleanup();
	
	currentState = state;
	getCurrentState()->Init();
}

State* GameEngine::getCurrentState()
{
	return States[currentState];
}

const sf::Input& GameEngine::getSteering()
{
	return steering;
}

bool GameEngine::run()
{
	window.SetFramerateLimit(100);
	window.Clear();
	
	ChangeState(MAINMENU);
	
	while (windowIsOpen)
	{
		getCurrentState()->EventHandling();
		
		while(window.GetEvent(event))
		{
			if(event.Type==sf::Event::Closed)
			{
				window.Close();
				windowIsOpen = false;
				break;
			}
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
			{
				switch (currentState)
				{
					case MAINMENU:
						window.Close();
						windowIsOpen = false;
						break;
					case EDITOR:
						ChangeState(MAINMENU);
						break;
					case GAME:
						ChangeState(MAINMENU);
						break;
				}
			}
			 if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::F))
			{
				if(fpsFlag == true)
					fpsFlag = false;
				else fpsFlag = true;
			}
			
			 getCurrentState()->GetEvents();
		}
		
		window.Clear( sf::Color( 0, 0, 0 ) );
		getCurrentState()->Display();

		Display();

		window.Display();
	}

	return 0;
}

sf::RenderWindow& GameEngine::getWindow()
{
	return window;
}

sf::View& GameEngine::getView()
{
	return View;
}

sf::Event& GameEngine::getEvent()
{
	return event;
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
