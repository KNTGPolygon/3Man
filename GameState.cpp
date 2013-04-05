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
	init = 1;
}

void GameState::Display()
{
	GameEngine::getInstance()->FlushRenderQueue();

	GameEngine::getInstance()->AddToRenderQueue((Drawable*)hero);

	map->showMap(&GameEngine::getInstance()->getWindow());
	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());

	GameEngine::getInstance()->ExecuteRenderQueue();
}

void GameState::EventHandling()
{
	hero->UpdatePosition();
	hero->GetEvent();
}

void GameState::GetEvents()
{

}

void GameState::Cleanup()
{
	delete hero;
	delete map;
	init = 0;
}
