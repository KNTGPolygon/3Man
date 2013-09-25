#include "GameEngine.h"

GameEngine::GameEngine(void):steering(window.GetInput())
{	
	window.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Integrator", sf::Style::Close);

	window.SetFramerateLimit(60);
	window.ShowMouseCursor(false);
	window.SetView(window.GetDefaultView());
	View.SetFromRect( sf::Rect<float>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) );

	States[GAME] = new GameState();
	States[MAINMENU] = new MainMenuState();
	States[OPTIONSMENU] = new OptionsMenuState();
	States[EDITOR] = new EditorState();
	currentState = NOSTATE;
	nextState = NOSTATE;
	
	time.Reset();
	currentTime=0;
	lastTime = 0;
	mainMenu = true;
	fpsFlag = true;
	devmode = false;

	strFps.SetPosition(5,5);
	strFps.SetScale(0.5,0.5);

	windowIsOpen = window.IsOpened();
		
	collisionQuadtree = new QuadtreeNode(0,0,640,640);
		
	if (!soundtrack.OpenFromFile("Data/Music/Aurora_down.ogg"))
	{
    // Error...
		std::cout<<"Cannot load file : Data/Music/Aurora_down.ogg\n";
	}
	soundtrack.SetVolume( 75.f );
	soundtrack.SetLoop( true );
	soundtrack.Play();
	//soundtrack.ge
}

GameEngine::~GameEngine(void)
{
	//freeResources(); ale to potem 
	delete collisionQuadtree;
	window.Clear();
	window.Close();
}

void GameEngine::Display()
{
	if(fpsFlag == true)
	{
		currentTime = time.GetElapsedTime();
		SetGameView();
		strFps.SetText("FPS = " + Util::int2str((int)(1/(currentTime-lastTime))) +
					   "\nFrame time = " + Util::flo2str(window.GetFrameTime()) +
					   "\nMouse: " + Util::int2str( GetMouseCoords().x ) + ", " + Util::int2str(GetMouseCoords().y ));
		SetDefaultView();
		window.Draw( strFps );
		lastTime = currentTime;
	}
	SetDefaultView();
	cursor.Display(&window);
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
	window.Clear();
	
	ChangeState(MAINMENU);
	
	while (windowIsOpen)
	{
		SwitchState();

		getCurrentState()->UpdateSystem();
		getCurrentState()->EventHandling();
		
		while(window.GetEvent(event))
		{
			if(event.Type==sf::Event::Closed)
			{
				window.Close();
				windowIsOpen = false;
				break;
			}
			if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::F))
				 fpsFlag = !fpsFlag;
			if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::G))
				devmode = !devmode;

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

bool GameEngine::Collision( SpriteExt* sprite1, SpriteExt* sprite2 )
{
	CollisionMask* mask1 = sprite1->getCollisionMask();
	CollisionMask* mask2 = sprite2->getCollisionMask();

	if ( mask1 == NULL || mask2 == NULL )
		return false;

	if ( mask1->getType() == BOX && mask2->getType() == BOX )
	{
		int Ax1 = (int)( sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Left );
		int Ax2 = (int)( sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Right );
		int Ay1 = (int)( sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Top );
		int Ay2 = (int)( sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Bottom );
		int Bx1 = (int)( sprite2->GetPosition().x-sprite2->GetCenter().x+((BoxMask*)mask2)->getRect().Left );
		int Bx2 = (int)( sprite2->GetPosition().x-sprite2->GetCenter().x+((BoxMask*)mask2)->getRect().Right );
		int By1 = (int)( sprite2->GetPosition().y-sprite2->GetCenter().y+((BoxMask*)mask2)->getRect().Top );
		int By2 = (int)( sprite2->GetPosition().y-sprite2->GetCenter().y+((BoxMask*)mask2)->getRect().Bottom );

		if ( Ax1 <= Bx2 && Ax2 >= Bx1 && Ay1 <= By2 && Ay2 >= By1 )
			return true;
		else return false;
	}

	if ( mask1->getType() == CIRCLE && mask2->getType() == CIRCLE )
	{
		int x1 = (int)( sprite1->GetPosition().x-sprite1->GetCenter().x+((CircleMask*)mask1)->getX() );
		int y1 = (int)( sprite1->GetPosition().y-sprite1->GetCenter().y+((CircleMask*)mask1)->getY() );
		int x2 = (int)( sprite2->GetPosition().x-sprite2->GetCenter().x+((CircleMask*)mask2)->getX() );
		int y2 = (int)( sprite2->GetPosition().y-sprite2->GetCenter().y+((CircleMask*)mask2)->getY() );
		int r1 = ((CircleMask*)mask1)->getRadius();
		int r2 = ((CircleMask*)mask2)->getRadius();

		if ( sqrt(pow((float)x1-x2,2)+pow((float)y1-y2,2)) <= r1+r2 )
			return true;
		else return false;
	}

	if ( (mask1->getType() == BOX && mask2->getType() == CIRCLE) ||  (mask1->getType() == CIRCLE && mask2->getType() == BOX))
	{
		if (mask1->getType() == CIRCLE)
		{
			SpriteExt* tmp = sprite1;
			sprite1 = sprite2;
			sprite2 = tmp;
			mask1 = sprite1->getCollisionMask();
			mask2 = sprite2->getCollisionMask();
		}

		int x1 = (int)( sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Left );
		int x2 = (int)( sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Right );
		int y1 = (int)( sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Top );
		int y2 = (int)( sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Bottom );

		int cx = (int)( sprite2->GetPosition().x-sprite2->GetCenter().x+((CircleMask*)mask2)->getX() );
		int cy = (int)( sprite2->GetPosition().y-sprite2->GetCenter().y+((CircleMask*)mask2)->getY() );
		int r = ((CircleMask*)mask2)->getRadius();

		if ( cx >= x1 && cx <= x2 && cy >= y1 && cy <= y2 )
			return true;
		else if ( sqrt(pow((float)x1-cx,2)+pow((float)y1-cy,2)) <= r ||
				  sqrt(pow((float)x2-cx,2)+pow((float)y1-cy,2)) <= r ||
				  sqrt(pow((float)x1-cx,2)+pow((float)y2-cy,2)) <= r ||
				  sqrt(pow((float)x2-cx,2)+pow((float)y2-cy,2)) <= r )
			return true;
		else if ( (abs(cx-x1) <= r && (cy-y1)*(cy-y2) < 0 ) ||
				  (abs(cx-x2) <= r && (cy-y1)*(cy-y2) < 0 ) ||
				  (abs(cy-y1) <= r && (cx-x1)*(cx-x2) < 0 ) ||
				  (abs(cy-y2) <= r && (cx-x1)*(cx-x2) < 0 ) )
			return true;
		else return false;
	}

	return false;
}
void GameEngine::SwitchWindowIsOpen(bool WindowIsOpen)
{
	windowIsOpen = WindowIsOpen;
}

void GameEngine::AddToCollisionQuadtree(SpriteExt* spr)
{
	collisionQuadtree->Add(spr);
}

bool GameEngine::DetectCollision(SpriteExt* spr)
{
	return collisionQuadtree->Collide(spr);
}

bool GameEngine::DetectCollision(SpriteExt* spr, std::string type)
{
	return collisionQuadtree->Collide(spr, type);
}

void GameEngine::DetectCollision(SpriteExt* spr, std::vector<SpriteExt*>& results)
{
	return collisionQuadtree->Collide(spr, results);
}

void GameEngine::DetectCollision(SpriteExt* spr, std::vector<SpriteExt*>& results, std::string type)
{
	return collisionQuadtree->Collide(spr, results, type);
}

void GameEngine::ClearCollisionQuadtree()
{
	collisionQuadtree->Clear();
}

void GameEngine::DisplayCollisionQuadtree()
{
	collisionQuadtree->Display(&window);
}

sf::RenderWindow& GameEngine::getWindow()
{
	return window;
}

sf::View& GameEngine::getView()
{
	return View;
}

void GameEngine::SetDefaultView()
{
	window.SetView(window.GetDefaultView());
}

void GameEngine::SetGameView()
{
	window.SetView(View);
}

sf::Event& GameEngine::getEvent()
{
	return event;
}
sf::Music& GameEngine::getMusic()
{
	return soundtrack;
}
Cursor& GameEngine::getCursor()
{
	return cursor;
}

sf::Vector2f GameEngine::GetMouseCoords()
{
	int mouse_x = steering.GetMouseX();
	int mouse_y = steering.GetMouseY();

	return window.ConvertCoords( mouse_x, mouse_y, &window.GetView() );
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
