#include "EditorState.h"

EditorState::EditorState():State()
{
	std::cout << "Konstruktor EditorState!" << std::endl;
}

void EditorState::Init()
{
	
	mapCreator = new MapCreator(GameEngine::getInstance()->getSteering());
	mapCreator->GetScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);

	inputBox = new InputBox(GameEngine::getInstance()->getSteering(),
					sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -100),
			       (float)(GameEngine::SCREEN_HEIGHT/2)),
				   "Rozmiar mapy"); 
	init = 1;
	state = SET_MAP_SIZE;
}

void EditorState::Display()
{
	if(state == SET_MAP_SIZE)
		{
			inputBox->Display(&GameEngine::getInstance()->getWindow());
		}
	else if (state == MAIN)
		{
		mapCreator->MoveCamera(&GameEngine::getInstance()->getView(), &GameEngine::getInstance()->getWindow());
		mapCreator->Display(&GameEngine::getInstance()->getWindow());
		}
}

void EditorState::EventHandling()
{
	if(state == MAIN)
	{
		mapCreator->GetSteeringEvent();
	}

}

void EditorState::GetEvents()
{

	sf::Event event = GameEngine::getInstance()->getEvent();
		if(state==SET_MAP_SIZE)
			{
			inputBox->HandleEvent(event);
			mapCreator->GetTextboxEvent(event, inputBox->GetString(), state);
			}
		else if (state == MAIN)
			{
			mapCreator->GetEvent(event);
			}

		if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
		{
			GameEngine::getInstance()->ChangeState(MAINMENU);
		}
}

void EditorState::Cleanup()
{
	if (state == MAIN)
		delete mapCreator;
	init = 0;
}

