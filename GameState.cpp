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

	tree[0] = new Tree(391,320);
	tree[1] = new Tree(179,28);
	tree[2] = new Tree(270,361);
	tree[3] = new Tree(464,122);
	tree[4] = new Tree(39,119);
	tree[5] = new Tree(312,56);
	tree[6] = new Tree(84,324);
	tree[7] = new Tree(42,208);
	tree[8] = new Tree(420,259);
	tree[9] = new Tree(272,110);
	tree[10] = new Tree(299,482);
	tree[11] = new Tree(54,342);
	tree[12] = new Tree(326,140);
	tree[13] = new Tree(94,389);
	tree[14] = new Tree(370,41);
	tree[15] = new Tree(182,261);
	tree[16] = new Tree(361,362);
	tree[17] = new Tree(290,132);
	tree[18] = new Tree(224,255);
	tree[19] = new Tree(254,264);

}

void GameState::Display()
{
	GameEngine::getInstance()->FlushRenderQueue();

	GameEngine::getInstance()->AddToRenderQueue((Drawable*)hero);
	for ( int i = 0; i < 20; i++ )
		GameEngine::getInstance()->AddToRenderQueue((Drawable*)tree[i]);

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
	for ( int i = 0; i < 20; i++ )
		tree[i]->Update();

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
	for ( int i = 0; i < 20; i++ )
		delete tree[i];
	for ( int i = 0; i < NUM_OF_ENEMIES; i++ )
		delete numbers[i];

	init = 0;
}
