#include "EditorState.h"

EditorState::EditorState():State()
{
}

void EditorState::Init()
{
	mapCreator = new MapCreator(GameEngine::getInstance()->getSteering());
	mapCreator->GetScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);
	init = 1;
}

void EditorState::Display()
{
	mapCreator->MoveCamera(&GameEngine::getInstance()->getView(), &GameEngine::getInstance()->getWindow());
	mapCreator->Display(&GameEngine::getInstance()->getWindow());
}

void EditorState::EventHandling()
{
	mapCreator->GetSteeringEvent();
}

void EditorState::GetEvents()
{
	mapCreator->GetEvent(GameEngine::getInstance()->getEvent());
}

void EditorState::Cleanup()
{

}

