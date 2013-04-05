#include "GameEngine.h"

GameEngine::GameEngine(void):steering(window.GetInput())
{	
	window.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "3Game");
	
	States[GAME] = new GameState();
	States[MAINMENU] = new MainMenuState();
	States[EDITOR] = new EditorState();
	currentState = NOSTATE;
	nextState = NOSTATE;
	
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
	nextState = state;
}

void GameEngine::SwitchState()
{
	if ( nextState == currentState || nextState == NOSTATE ) return;

	if ( currentState != NOSTATE )
		getCurrentState()->Cleanup();
	
	currentState = nextState;
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
		SwitchState();

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
					case NOSTATE:
						window.Close();
						windowIsOpen = false;
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

void GameEngine::AddToRenderQueue(Drawable* obj)
{
	RenderQueue.push(obj);
}

void GameEngine::FlushRenderQueue()
{
	while (!RenderQueue.empty())
		RenderQueue.pop();
}

void GameEngine::ExecuteRenderQueue()
{
	while (!RenderQueue.empty())
	{
		RenderQueue.top()->Display(&window);
		RenderQueue.pop();
	}
}

static bool Collision( SpriteExt& sprite1, SpriteExt& sprite2 )
{
	CollisionMask* mask1 = sprite1.getCollisionMask();
	CollisionMask* mask2 = sprite2.getCollisionMask();

	if ( mask1 == NULL || mask2 == NULL )
		return false;

	if ( mask1->getType() == BOX && mask2->getType() == BOX )
	{
		return ((BoxMask*)mask1)->getRect().Intersects( ((BoxMask*)mask1)->getRect(), &((BoxMask*)mask2)->getRect() );
	}

	return false;
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
