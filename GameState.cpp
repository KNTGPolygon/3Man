#include "GameState.h"

GameState::GameState():State()
{
	std::cout << "Konstruktor GameState!" << std::endl;
}

void GameState::Init()
{
	GameEngine::getInstance()->FlushCollisionList();
	hero = new Hero(GameEngine::getInstance()->getSteering(),2);
	hero->PutScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);
	map = new Maps("Data/Maps/Test.map");
	pirate = new Enemy(sf::Vector2i(400,300));

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
	map->showMap(&GameEngine::getInstance()->getWindow(), hero->GetPosition());
	pirate->Display(&GameEngine::getInstance()->getWindow());
	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());
	
	GameEngine::getInstance()->ExecuteRenderQueue();
}

void GameState::EventHandling()
{
	hero->UpdatePosition();
	hero->GetEvent();
	//pirate->Logic(sf::Vector2i(500,500));
	pirate->SetHeroPosition(hero->GetPosition());
	pirate->AI();

	for ( int i = 0; i < 20; i++ )
		tree[i]->Update();
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
	for ( int i = 0; i < 20; i++ )
		delete tree[i];

	init = 0;
}
