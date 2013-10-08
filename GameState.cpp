#include "GameState.h"
#include "Cursor.h"
#include "Fx/EffectLayer.h"

GameState::GameState():State()
{
	std::cout << "Konstruktor GameState!" << std::endl;
}

void GameState::Init()
{
	GameEngine::getInstance()->getCursor().setType(CROSSHAIR);
	GameEngine::getInstance()->pathfinder->SetNumberOfMobs( 0 );
	DrawableEntityList.clear();

	hero = new Hero(GameEngine::getInstance()->getSteering(),2);
	hero->PutScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);

	map = new Maps("Data/Maps/Test.map");
	numberOfObjects = map->getNoOfObjects();
	arrayOfObjects = map->getMapGameObjects();
	mapPixelatedSize = map->getSize() * 64;

	pirate = new Enemy(sf::Vector2i(100,100),1);
	GameEngine::getInstance()->pathfinder->Initialization( GameEngine::getInstance()->GetObjects(),
														   GameEngine::getInstance()->GetGridSize().x,
														   GameEngine::getInstance()->GetGridSize().y );
	
	DrawableEntityList.push_back(hero);
	DrawableEntityList.push_back(pirate);


	for( int i = 0; i < numberOfObjects ; i++ )
		DrawableEntityList.push_back( arrayOfObjects[i] );
	std::cout << "DEL size: " << DrawableEntityList.size() << std::endl;

	counter = 0;
	lastPath[0] = sf::Vector2i(64,100);
	iterator = 0;
}

void GameState::UpdateSystem()
{


	if ( GameEngine::getInstance()->getSteering().IsKeyDown( sf::Key::J ) )
	{
		pirate->SetAIState( Enemy::FOLLOW );
	}	

	GameEngine::getInstance()->ClearCollisionQuadtree();
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		DrawableEntityList[i]->UpdateSystem();
	counter++;
}

void GameState::Display()
{
	GameEngine::getInstance()->SetGameView();
	GameEngine::getInstance()->FlushRenderQueue();

	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		GameEngine::getInstance()->AddToRenderQueue(DrawableEntityList[i]);

	map->showMap(&GameEngine::getInstance()->getWindow(), hero->GetPosition());

	GameEngine::getInstance()->ExecuteRenderQueue();

	EffectLayer::getInstance()->DrawEffects();

	if(GameEngine::getInstance()->devmode)
		GameEngine::getInstance()->DisplayCollisionQuadtree();

	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());
}

void GameState::EventHandling()
{
	GameEngine::getInstance()->SetGameView();
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		DrawableEntityList[i]->EventHandling();
}

void GameState::GetEvents()
{
	sf::Event event = GameEngine::getInstance()->getEvent();
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
	{
		GameEngine::getInstance()->ChangeState(MAINMENU);
	}
}

void GameState::Cleanup()
{
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		delete DrawableEntityList[i];
	//delete GameEngine::getInstance()->pathfinder;
	//if( GameEngine::getInstance()->pathfinder != NULL )
	//	GameEngine::getInstance()->pathfinder = NULL;
	init = 0;
}
