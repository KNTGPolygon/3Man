#include "MainMenuState.h"
#include "ImageManager.h"

MainMenuState::MainMenuState():State()
{
	std::cout <<  "Konstruktor MainMenuState!" << std::endl;
}

void MainMenuState::Init()
{
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

	title.SetImage(ImageManager::getInstance()->loadImage("Data/Textures/title.png"));
	title.SetCenter(0, 0);
	title.SetPosition(105,50);
	info.SetText("alpha version");
	info.SetScale(0.5, 0.5);
	info.SetPosition(560, 140);

	init = 1;
}

void MainMenuState::UpdateSystem()
{
}

void MainMenuState::Display()
{
	GameEngine::getInstance()->SetDefaultView();
	mapEditor->Display( &GameEngine::getInstance()->getWindow() );
	gameStart->Display( &GameEngine::getInstance()->getWindow() );
	options->Display( &GameEngine::getInstance()->getWindow() );
	exit->Display( &GameEngine::getInstance()->getWindow() );
	GameEngine::getInstance()->getWindow().Draw(title);
	GameEngine::getInstance()->getWindow().Draw(info);
}

void MainMenuState::EventHandling()
{
	GameEngine::getInstance()->SetDefaultView();
	gameStart->GetEvent();
	mapEditor->GetEvent();
	options->GetEvent();
	exit->GetEvent();
	
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
	init = 0;
}

