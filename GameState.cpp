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
	tree[0] = new Tree(300,300);
	tree[1] = new Tree(400,150);
	tree[2] = new Tree(600,500);
	tree[3] = new Tree(340,500);
	tree[4] = new Tree(420,180);
	tree[5] = new Tree(450,190);
	tree[6] = new Tree(340,300);
	tree[7] = new Tree(370,326);
	init = 1;
}

void GameState::Display()
{
	GameEngine::getInstance()->FlushRenderQueue();

	GameEngine::getInstance()->AddToRenderQueue((Drawable*)hero);
	for ( int i = 0; i < 8; i++ )
		GameEngine::getInstance()->AddToRenderQueue((Drawable*)tree[i]);

	map->showMap(&GameEngine::getInstance()->getWindow());
	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());

	GameEngine::getInstance()->ExecuteRenderQueue();
}

void GameState::EventHandling()
{
	hero->UpdatePosition();
	hero->GetEvent();
	for ( int i = 0; i < 8; i++ )
		tree[i]->Update();
}

void GameState::GetEvents()
{

}

void GameState::Cleanup()
{
	delete hero;
	delete map;
	for ( int i = 0; i < 8; i++ )
		delete tree[i];

	init = 0;
}
