#include "GameState.h"

GameState::GameState():State()
{
	std::cout << "Konstruktor GameState!" << std::endl;
}

void GameState::Init()
{
	hero = new Hero(GameEngine::getInstance()->getSteering(),2);
	hero->PutScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);

	map = new Maps("Data/Maps/Test.map");
	numberOfObjects = map->getNoOfObjects();
	arrayOfObjects = map->getMapGameObjects();
	mapPixelatedSize = map->getSize() * 64;

	pirate = new Enemy(sf::Vector2i(400,300));
	seven  = new Number(sf::Vector2i(300,300),7);
	numbers = new Number*[NUM_OF_ENEMIES];

	numbers[0] = new Number(sf::Vector2i(330,300),-1);
	numbers[1] = new Number(sf::Vector2i(300,310),-2);
	numbers[2] = new Number(sf::Vector2i(350,320),-3);
	numbers[3] = new Number(sf::Vector2i(310,330),-4);
	numbers[4] = new Number(sf::Vector2i(250,340),-5);

	wall[0] = new Wall(100, 100);
	wall[1] = new Wall(132, 100);
	wall[2] = new Wall(164, 100);
	wall[3] = new Wall(196, 100);
	wall[4] = new Wall(196, 116);
	wall[5] = new Wall(196, 132);
	wall[6] = new Wall(228, 132);
	wall[7] = new Wall(260, 132);
	wall[8] = new Wall(292, 132);
	wall[9] = new Wall(324, 132);

}

void GameState::Display()
{
	GameEngine::getInstance()->FlushRenderQueue();

	GameEngine::getInstance()->AddToRenderQueue((Drawable*)hero);

	for ( int i = 0; i < 10; i++ )
		GameEngine::getInstance()->AddToRenderQueue(wall[i]);

	for ( int i = 0; i < numberOfObjects; i++ )
		GameEngine::getInstance()->AddToRenderQueue((Drawable*)arrayOfObjects[i]);


	map->showMap(&GameEngine::getInstance()->getWindow(), hero->GetPosition());
	pirate->Display(&GameEngine::getInstance()->getWindow());
	seven->Display(&GameEngine::getInstance()->getWindow());
	for( int i = 0; i < NUM_OF_ENEMIES ; i++)
		//numbers[i]->Display(&GameEngine::getInstance()->getWindow());
		GameEngine::getInstance()->AddToRenderQueue((Drawable*)numbers[i]);
	
	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());
	
	GameEngine::getInstance()->ExecuteRenderQueue();

	if(GameEngine::getInstance()->devmode)
		GameEngine::getInstance()->DisplayCollisionQuadtree();

}

void GameState::EventHandling()
{
	GameEngine::getInstance()->ClearCollisionQuadtree();

	hero->UpdatePosition();
	hero->GetEvent(mapPixelatedSize);
	pirate->SetHeroPosition(hero->GetPosition());
	pirate->AI();
	for( int i = 0; i < NUM_OF_ENEMIES ; i++)
		{
			numbers[i]->SetHeroPosition(hero->GetPosition());
			numbers[i]->AI();
		}
	seven->SetHeroPosition(hero->GetPosition());
	seven->AI();

	for ( int i = 0; i < 10; i++ )
		wall[i]->Update();

	for ( int i = 0; i < numberOfObjects; i++ )
		arrayOfObjects[i]->Update();
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
	delete hero;
	delete map;
	delete pirate;
	delete seven;
	for ( int i = 0; i < 10; i++ )
		delete wall[i];
	for ( int i = 0; i < NUM_OF_ENEMIES; i++ )
		delete numbers[i];

	init = 0;
}
