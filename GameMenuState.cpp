#include "GameMenuState.h"

GameMenuState::GameMenuState():State()
{
	std::cout <<  "Konstruktor GameMenuState!" << std::endl;
}

void GameMenuState::Init()
{
	GameEngine::getInstance()->getCursor().setType(ARROW);
	
	gameStart = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)GameEngine::SCREEN_HEIGHT/2),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Nowa gra");
	userGameStart = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 + 100)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Wlasna mapa");
	exit = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 + 200)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Wroc");
	
	title.SetImage(ImageManager::getInstance()->loadImage("Data/Textures/title.png"));
	title.SetCenter(0, 0);
	title.SetPosition(105,50);
	info.SetText("alpha version");
	info.SetScale(0.5, 0.5);
	info.SetPosition(560, 140);


	init = 1;
}

void GameMenuState::UpdateSystem()
{
}

void GameMenuState::Display()
{
	GameEngine::getInstance()->SetDefaultView();
	gameStart->Display( &GameEngine::getInstance()->getWindow() );
	userGameStart->Display( &GameEngine::getInstance()->getWindow() );
	exit->Display( &GameEngine::getInstance()->getWindow() );
	GameEngine::getInstance()->getWindow().Draw(title);
	GameEngine::getInstance()->getWindow().Draw(info);

}

void GameMenuState::EventHandling()
{
	GameEngine::getInstance()->SetDefaultView();
	gameStart->GetEvent();
	userGameStart->GetEvent();
	exit->GetEvent();
	
	if ( exit->pressed )
	{
		GameEngine::getInstance()->ChangeState( MAINMENU );
	}
	if ( userGameStart->pressed )
		GameEngine::getInstance()->ChangeState( USERGAME );
	if ( gameStart->pressed )
		GameEngine::getInstance()->ChangeState(GAME);
		
}

void GameMenuState::GetEvents()
{
	sf::Event event = GameEngine::getInstance()->getEvent();
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
	{
		GameEngine::getInstance()->getWindow().Close();
		GameEngine::getInstance()->SwitchWindowIsOpen( false );
	}
}

void GameMenuState::Cleanup()
{
	delete userGameStart;
	delete gameStart;
	delete exit;
	init = 0;
}

