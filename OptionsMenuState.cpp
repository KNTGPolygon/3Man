#include "OptionsMenuState.h"

OptionsMenuState::OptionsMenuState():State()
{
	std::cout <<  "Konstruktor OptionsMenuState!" << std::endl;
}

void OptionsMenuState::Init()
{
	GameEngine::getInstance()->getWindow().SetView( GameEngine::getInstance()->getWindow().GetDefaultView() );
	
	music =    new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 - 100.0)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Muzyka");
	sounds =   new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)GameEngine::SCREEN_HEIGHT/2),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Dzwieki");      
	mainMenu = new Button(GameEngine::getInstance()->getSteering(),
			       sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 -50.0),
			       (float)(GameEngine::SCREEN_HEIGHT/2 + 150)),
			       sf::Vector2f(100.0,50.0),
			       sf::Color(125,125,125),
			       "Powrot");
	musicTextBox =  new TextBox(sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 +100 ),
			       (float)( GameEngine::SCREEN_HEIGHT/2 - 100.0 ) ),
				   sf::Vector2f((float)(50),(float)(50)) );
	soundTextBox =  new TextBox(sf::Vector2f((float)(GameEngine::SCREEN_WIDTH/2 +100 ),
			       (float)(GameEngine::SCREEN_HEIGHT/2 )),
				   sf::Vector2f((float)(50),(float)(50)) );
	
	
	musicTextBox->SetText( "Tak" );
	musicTextBox->SetTextPosition( sf::Vector2f( musicTextBox->GetTextBoxPosition().x + 10 ,musicTextBox->GetTextBoxPosition().y + 15 ) );

	soundTextBox->SetText( "Nie" );
	soundTextBox->SetTextPosition( sf::Vector2f( soundTextBox->GetTextBoxPosition().x + 10 ,soundTextBox->GetTextBoxPosition().y + 15 ) );
	init = 1;
}

void OptionsMenuState::UpdateSystem()
{
}

void OptionsMenuState::Display()
{
	sounds->Display(&GameEngine::getInstance()->getWindow());
	music->Display(&GameEngine::getInstance()->getWindow());
	mainMenu->Display(&GameEngine::getInstance()->getWindow());
	musicTextBox->Display(&GameEngine::getInstance()->getWindow());
	soundTextBox->Display(&GameEngine::getInstance()->getWindow());
}

void OptionsMenuState::EventHandling()
{
	music->GetEvent();
	sounds->GetEvent();
	mainMenu->GetEvent();
	
	if ( mainMenu->pressed )
	{
		GameEngine::getInstance()->ChangeState(MAINMENU);
	}
		
	if ( music->singlePressed )
	{
		if ( GameEngine::getInstance()->getMusic().GetStatus() == sf::Sound::Playing )
		{
			GameEngine::getInstance()->getMusic().Stop();
			musicTextBox->SetText( "Nie" );
		}
		else if ( GameEngine::getInstance()->getMusic().GetStatus() == sf::Sound::Stopped )
		{
			GameEngine::getInstance()->getMusic().Play();
			musicTextBox->SetText( "Tak" );
		}

	}		
	if ( sounds->singlePressed )
	{
		std::string temp = soundTextBox->GetText().GetText();	
		if( temp == "Nie" )
		{
			soundTextBox->SetText("NIE!");
		}
		else soundTextBox->SetText("Nie");
	}
}

void OptionsMenuState::GetEvents()
{
	sf::Event event = GameEngine::getInstance()->getEvent();
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
	{
		GameEngine::getInstance()->getWindow().Close();
		GameEngine::getInstance()->SwitchWindowIsOpen( false );
	}
}

void OptionsMenuState::Cleanup()
{
	delete sounds;
	delete music;
	delete mainMenu;
	delete musicTextBox;
	delete soundTextBox;
	init = 0;
}

