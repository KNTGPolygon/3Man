#include "GameState.h"
#include "Cursor.h"
#include "Fx/EffectLayer.h"
#include "Levels/Armor.h"
#include "Levels/Gui.h"
#include "Levels/Invincibility.h"

bool GameState::restart_level;
bool GameState::death_effect;
sf::Clock GameState::death_anim_timer;

GameState::GameState():State()
{
	std::cout << "Konstruktor GameState!" << std::endl;
}

void GameState::Init()
{
	restart_level = false;
	death_effect = false;
	death_anim_timer.Reset();
	GameEngine::getInstance()->getCursor().setType(CROSSHAIR);
	if( GameEngine::getInstance()->GetCurrentState() == USERGAME )
	current_level = "Data/Maps/UserMap.map";
	else
	current_level = "Data/Maps/Test.map";
	LoadLevel(current_level);
}

void GameState::LoadLevel(const std::string& filename)
{
	GameEngine::getInstance()->pathfinder->SetNumberOfMobs( 0 );
	DrawableEntityList.clear();
	hero = new Hero(GameEngine::getInstance()->getSteering(),2);
	hero->PutScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);

	map = new Maps(filename);
	arrayOfObjects = map->getMapGameObjects();
	numberOfEnemies = map->GetListOfEnemies().size();
	vectorOfEnemies = map->GetListOfEnemies();

	vectorOfActiveObjects = map->getMapActiveGameObjects();
	mapPixelatedSize = map->getSize() * 64;

	pirate = new Enemy(sf::Vector2i(100,100),1);

	enemy = new Enemy*[numberOfEnemies ];
	for(int i = 0 ; i < numberOfEnemies ; i++ )
		enemy[i] = new Enemy(sf::Vector2i(vectorOfEnemies[i].x,vectorOfEnemies[i].y ),vectorOfEnemies[i].z );


	GameEngine::getInstance()->pathfinder->Initialization( GameEngine::getInstance()->GetObjects(),
														   GameEngine::getInstance()->GetGridSize().x,
														   GameEngine::getInstance()->GetGridSize().y );
	
	DrawableEntityList.push_back(hero);
	DrawableEntityList.push_back(pirate);
	DrawableEntityList.push_back(new Armor(384, 384));
	DrawableEntityList.push_back(new Invincibility(480, 480));
	DrawableEntityList.push_back(new Gui(GameEngine::SCREEN_WIDTH,GameEngine::SCREEN_HEIGHT));

	for( int i = 0; i < numberOfEnemies ; i++ )
		DrawableEntityList.push_back( enemy[i] );



	for( int i = 0; i < arrayOfObjects.size() ; i++ )
	{
		if ( arrayOfObjects.at(i)->getType() == 4 )
			DrawableEntityList.push_back( new Wall(arrayOfObjects.at(i)->GetPosition().x, arrayOfObjects.at(i)->GetPosition().y) );
		else
			DrawableEntityList.push_back( arrayOfObjects.at(i) );
	}

	for( int i = 0; i < vectorOfActiveObjects.size() ; i++ )
	{
		DrawableEntityList.push_back( vectorOfActiveObjects.at(i) );
	}

	std::cout << "DEL size: " << DrawableEntityList.size() << std::endl;

	counter = 0;
	lastPath[0] = sf::Vector2i(64,100);
	iterator = 0;
}

void GameState::ClearLevel()
{
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		delete DrawableEntityList[i];
}

void GameState::UpdateSystem()
{


	if ( GameEngine::getInstance()->getSteering().IsKeyDown( sf::Key::J ) )
	{
		pirate->SetAIState( Enemy::FOLLOW );
	}	

	GameEngine::getInstance()->ClearCollisionQuadtree();
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		DrawableEntityList[i]->UpdateSystem();
	counter++;
}

void GameState::Display()
{
	GameEngine::getInstance()->SetGameView();
	GameEngine::getInstance()->FlushRenderQueue();

	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		GameEngine::getInstance()->AddToRenderQueue(DrawableEntityList[i]);

	map->showMap(&GameEngine::getInstance()->getWindow(), hero->GetPosition());

	GameEngine::getInstance()->ExecuteRenderQueue();

	HeroDeathEffect();

	EffectLayer::getInstance()->DrawEffects();

	if(GameEngine::getInstance()->devmode)
		GameEngine::getInstance()->DisplayCollisionQuadtree();

	hero->SetCamera(&GameEngine::getInstance()->getView(),&GameEngine::getInstance()->getWindow());
}

void GameState::EventHandling()
{
	GameEngine::getInstance()->SetGameView();
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		DrawableEntityList[i]->EventHandling();
}

void GameState::GetEvents()
{
	sf::Event event = GameEngine::getInstance()->getEvent();
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
	{
		GameEngine::getInstance()->ChangeState(MAINMENU);
	}
}

void GameState::HeroDeathEffect()
{
	if ( death_effect )
	{
		sf::PostFX& hero_death = EffectLayer::getInstance()->AddEffect(Fx::HeroDeath);

		hero_death.SetParameter("screen", (float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT);

		float _cos = cos(2*death_anim_timer.GetElapsedTime());
		hero_death.SetParameter("circle",
						Hero::myPosition.x-GameEngine::getInstance()->getView().GetRect().Left,
						Hero::myPosition.y-GameEngine::getInstance()->getView().GetRect().Top,
						500*_cos*_cos );
		if ( death_anim_timer.GetElapsedTime() > M_PI/4 && GameState::restart_level )
		{
			ClearLevel();
			LoadLevel(current_level);
			restart_level = false;
		}
		if ( death_anim_timer.GetElapsedTime() > M_PI/2 )
			death_effect = false;
	}
}

void GameState::Cleanup()
{
	ClearLevel();
	//delete GameEngine::getInstance()->pathfinder;
	//if( GameEngine::getInstance()->pathfinder != NULL )
	//	GameEngine::getInstance()->pathfinder = NULL;
	init = 0;
}
