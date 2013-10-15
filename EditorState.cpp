#include "EditorState.h"

EditorState::EditorState():State()
{
	std::cout << "Konstruktor EditorState!" << std::endl;
}

void EditorState::Init()
{
	GameEngine::getInstance()->getCursor().setType(ARROW);
	
	mapCreator = new MapCreator(GameEngine::getInstance()->getSteering());
	mapCreator->GetScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);

	inputBox = new InputBox(GameEngine::getInstance()->getSteering(),
					sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -100),
			       (float)(GameEngine::SCREEN_HEIGHT/2)),
				   ""); 
		textBox = new TextBox(sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -175.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 - 250)),
			       sf::Vector2f(350.0,150.0),
			       sf::Color(61,61,61),
			       " Edytor do tworzenia map:\n Zalecana wielkosc mapy 10 - 1000 \n Klawiszologia : \n CTRL + L - Wczytanie bierzacej mapy\n Shift + LPM - Usuniecie obiektu\n Dyskietka - Zapis mapy do pliku");
		textBox1 = new TextBox(sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -230.0),
			       (float)( GameEngine::SCREEN_HEIGHT/2) ),
			       sf::Vector2f(130.0,30.0),
			       sf::Color(61,61,61),"Rozmiar mapy ");
	init = 1;
	state = SET_MAP_SIZE;
}

void EditorState::UpdateSystem()
{
}

void EditorState::Display()
{
	GameEngine::getInstance()->SetDefaultView();
	if(state == SET_MAP_SIZE)
		{
			inputBox->Display(&GameEngine::getInstance()->getWindow());
			textBox->Display(&GameEngine::getInstance()->getWindow());
			textBox1->Display(&GameEngine::getInstance()->getWindow());
		}
	else if (state == MAIN)
		{
		mapCreator->MoveCamera(&GameEngine::getInstance()->getView(), &GameEngine::getInstance()->getWindow());
		mapCreator->Display(&GameEngine::getInstance()->getWindow());
		}
}

void EditorState::EventHandling()
{
	GameEngine::getInstance()->SetDefaultView();
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
				if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Return))
				{
					std::string tempStr = inputBox->GetString();	

					mapCreator->GetTextboxEvent(event, tempStr , state);
				}
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
	delete textBox;
	delete inputBox;
	init = 0;
}

