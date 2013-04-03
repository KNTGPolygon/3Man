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
	map->showMap(&GameEngine::getInstance()->getWindow());
	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());
	hero->Display(&GameEngine::getInstance()->getWindow());
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
