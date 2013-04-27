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
	devmode = true;

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
	
	collisionQuadtree = new QuadtreeNode(0,0,600,600);

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
		int Ax1 = sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Left;
		int Ax2 = sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Right;
		int Ay1 = sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Top;
		int Ay2 = sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Bottom;
		int Bx1 = sprite2->GetPosition().x-sprite2->GetCenter().x+((BoxMask*)mask2)->getRect().Left;
		int Bx2 = sprite2->GetPosition().x-sprite2->GetCenter().x+((BoxMask*)mask2)->getRect().Right;
		int By1 = sprite2->GetPosition().y-sprite2->GetCenter().y+((BoxMask*)mask2)->getRect().Top;
		int By2 = sprite2->GetPosition().y-sprite2->GetCenter().y+((BoxMask*)mask2)->getRect().Bottom;

		if ( Ax1 <= Bx2 && Ax2 >= Bx1 && Ay1 <= By2 && Ay2 >= By1 )
			return true;
		else return false;
	}

	if ( mask1->getType() == CIRCLE && mask2->getType() == CIRCLE )
	{
		int x1 = sprite1->GetPosition().x-sprite1->GetCenter().x+((CircleMask*)mask1)->getX();
		int y1 = sprite1->GetPosition().y-sprite1->GetCenter().y+((CircleMask*)mask1)->getY();
		int x2 = sprite2->GetPosition().x-sprite2->GetCenter().x+((CircleMask*)mask2)->getX();
		int y2 = sprite2->GetPosition().y-sprite2->GetCenter().y+((CircleMask*)mask2)->getY();
		int r1 = ((CircleMask*)mask1)->getRadius();
		int r2 = ((CircleMask*)mask2)->getRadius();

		if ( sqrt(pow(x1-x2,2)+pow(y1-y2,2)) <= r1+r2 )
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

		int x1 = sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Left;
		int x2 = sprite1->GetPosition().x-sprite1->GetCenter().x+((BoxMask*)mask1)->getRect().Right;
		int y1 = sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Top;
		int y2 = sprite1->GetPosition().y-sprite1->GetCenter().y+((BoxMask*)mask1)->getRect().Bottom;

		int cx = sprite2->GetPosition().x-sprite2->GetCenter().x+((CircleMask*)mask2)->getX();
		int cy = sprite2->GetPosition().y-sprite2->GetCenter().y+((CircleMask*)mask2)->getY();
		int r = ((CircleMask*)mask2)->getRadius();

		if ( cx >= x1 && cx <= x2 && cy >= y1 && cy <= y2 )
			return true;
		else if ( sqrt(pow(x1-cx,2)+pow(y1-cy,2)) <= r ||
				  sqrt(pow(x2-cx,2)+pow(y1-cy,2)) <= r ||
				  sqrt(pow(x1-cx,2)+pow(y2-cy,2)) <= r ||
				  sqrt(pow(x2-cx,2)+pow(y2-cy,2)) <= r )
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
void GameEngine::FlushCollisionList()
{
	CollisionList.clear();
}

void GameEngine::AddToCollisionList( SpriteExt* spr )
{
	CollisionList.push_back(spr);
}

std::vector<SpriteExt*>& GameEngine::getCollisionList()
{
	return CollisionList;
}

void GameEngine::AddToCollisionQuadtree(SpriteExt* spr)
{
	collisionQuadtree->Add(spr);
}

bool GameEngine::DetectCollision(SpriteExt* spr)
{
	return collisionQuadtree->Collide(spr);
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
