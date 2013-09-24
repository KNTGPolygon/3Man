#include "MainMenuState.h"

MainMenuState::MainMenuState():State()
{
	std::cout <<  "Konstruktor MainMenuState!" << std::endl;
}

void MainMenuState::Init()
{
	GameEngine::getInstance()->getView().SetHalfSize((float)GameEngine::SCREEN_WIDTH/2,(float)GameEngine::SCREEN_HEIGHT/2);
	GameEngine::getInstance()->getView().SetCenter((float)GameEngine::SCREEN_WIDTH/2,(float)GameEngine::SCREEN_HEIGHT/2);
	GameEngine::getInstance()->getWindow().SetView(GameEngine::getInstance()->getView());
 	
	GameEngine::getInstance()->getCursor().setType(ARROW);


	
	mapEditor = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)GameEngine::SCREEN_HEIGHT/2),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Edytor");
			       
	gameStart = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 - 100.0)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Gra");
	options = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 + 100)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Opcje");
	exit = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 + 200)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Wyjscie");

	inputBox = new InputBox(GameEngine::getInstance()->getSteering(),
					sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -100),
			       (float)(GameEngine::SCREEN_HEIGHT/2 - 150.0))); 

	init = 1;
}

void MainMenuState::Display()
{
	mapEditor->Display( &GameEngine::getInstance()->getWindow() );
	gameStart->Display( &GameEngine::getInstance()->getWindow() );
	options->Display( &GameEngine::getInstance()->getWindow() );
	exit->Display( &GameEngine::getInstance()->getWindow() );
	inputBox->Display( &GameEngine::getInstance()->getWindow() );
}

void MainMenuState::EventHandling()
{
	gameStart->GetEvent();
	mapEditor->GetEvent();
	options->GetEvent();
	exit->GetEvent();
	inputBox->HandleEvent(GameEngine::getInstance()->getEvent());
	
	if ( exit->pressed )
	{
		GameEngine::getInstance()->getWindow().Close();
		GameEngine::getInstance()->SwitchWindowIsOpen( false );
	}
	if ( options->pressed )
		GameEngine::getInstance()->ChangeState( OPTIONSMENU );
	if ( gameStart->pressed )
		GameEngine::getInstance()->ChangeState(GAME);
		
	if ( mapEditor->pressed )
		GameEngine::getInstance()->ChangeState(EDITOR);
}

void MainMenuState::GetEvents()
{
	sf::Event event = GameEngine::getInstance()->getEvent();
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
	{
		GameEngine::getInstance()->getWindow().Close();
		GameEngine::getInstance()->SwitchWindowIsOpen( false );
	}
}

void MainMenuState::Cleanup()
{
	delete mapEditor;
	delete gameStart;
	delete exit;
	delete inputBox;
	init = 0;
}

