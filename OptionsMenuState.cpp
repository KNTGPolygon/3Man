#include "OptionsMenuState.h"

OptionsMenuState::OptionsMenuState():State()
{
	std::cout <<  "Konstruktor OptionsMenuState!" << std::endl;
}

void OptionsMenuState::Init()
{
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
	
	
	musicTextBox->SetText( GameEngine::getInstance()->getMusic().GetStatus() == sf::Sound::Playing ? "Tak" : "Nie" );
	musicTextBox->SetTextPosition( sf::Vector2f( musicTextBox->GetTextBoxPosition().x + 10 ,musicTextBox->GetTextBoxPosition().y + 15 ) );

	soundTextBox->SetText( GameEngine::getInstance()->Sounds() ? "Tak" : "Nie" );
	soundTextBox->SetTextPosition( sf::Vector2f( soundTextBox->GetTextBoxPosition().x + 10 ,soundTextBox->GetTextBoxPosition().y + 15 ) );

	title.SetImage(ImageManager::getInstance()->loadImage("Data/Textures/title.png"));
	title.SetCenter(0, 0);
	title.SetPosition(105,50);
	info.SetText("alpha version");
	info.SetScale(0.5, 0.5);
	info.SetPosition(560, 140);

	init = 1;
}

void OptionsMenuState::UpdateSystem()
{
}

void OptionsMenuState::Display()
{
	GameEngine::getInstance()->SetDefaultView();
	sounds->Display(&GameEngine::getInstance()->getWindow());
	music->Display(&GameEngine::getInstance()->getWindow());
	mainMenu->Display(&GameEngine::getInstance()->getWindow());
	musicTextBox->Display(&GameEngine::getInstance()->getWindow());
	soundTextBox->Display(&GameEngine::getInstance()->getWindow());
	GameEngine::getInstance()->getWindow().Draw(title);
	GameEngine::getInstance()->getWindow().Draw(info);
}

void OptionsMenuState::EventHandling()
{
	GameEngine::getInstance()->SetDefaultView();
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
			GameEngine::getInstance()->SetSounds(true);
			soundTextBox->SetText("Tak");
		}
		else
		{
			GameEngine::getInstance()->SetSounds(false);
			soundTextBox->SetText("Nie");
		}
	}
}

void OptionsMenuState::GetEvents()
{
	sf::Event event = GameEngine::getInstance()->getEvent();
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
	{
		GameEngine::getInstance()->ChangeState(MAINMENU);
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

