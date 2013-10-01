#include "GameState.h"
#include "Cursor.h"

GameState::GameState():State()
{
	std::cout << "Konstruktor GameState!" << std::endl;
}

void GameState::Init()
{
	GameEngine::getInstance()->getCursor().setType(CROSSHAIR);

	DrawableEntityList.clear();

	hero = new Hero(GameEngine::getInstance()->getSteering(),2);
	hero->PutScreenSize(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);

	map = new Maps("Data/Maps/Test.map");
	numberOfObjects = map->getNoOfObjects();
	arrayOfObjects = map->getMapGameObjects();
	mapPixelatedSize = map->getSize() * 64;

	pirate = new Enemy(sf::Vector2i(400,300));
	seven  = new Number(sf::Vector2i(300,300),7);
	numbers = new Number*[NUM_OF_ENEMIES];

	numbers[0] = new Number(sf::Vector2i(330,300),-1);
	numbers[1] = new Number(sf::Vector2i(300,310),-2);
	numbers[2] = new Number(sf::Vector2i(350,320),-3);
	numbers[3] = new Number(sf::Vector2i(310,330),-4);
	numbers[4] = new Number(sf::Vector2i(250,340),-5);

	float t = 32.0f;
	DrawableEntityList.push_back(new Wall(3*t, 3*t));
	DrawableEntityList.push_back(new Wall(4*t, 3*t));
	DrawableEntityList.push_back(new Wall(5*t, 3*t));
	DrawableEntityList.push_back(new Wall(6*t, 3*t));
	DrawableEntityList.push_back(new Wall(10*t, 10*t));
	DrawableEntityList.push_back(new Wall(6*t, 4*t));
	DrawableEntityList.push_back(new Wall(7*t, 4*t));
	DrawableEntityList.push_back(new Wall(8*t, 4*t));
	DrawableEntityList.push_back(new Wall(9*t, 4*t));
	DrawableEntityList.push_back(new Wall(10*t, 4*t));
	DrawableEntityList.push_back(new Wall(8*t, 5*t));
	DrawableEntityList.push_back(new Wall(8*t, 6*t));
	DrawableEntityList.push_back(new Wall(8*t, 7*t));
	DrawableEntityList.push_back(new Wall(8*t, 8*t));
	DrawableEntityList.push_back(new Wall(7*t, 8*t));
	DrawableEntityList.push_back(new Wall(6*t, 8*t));
	DrawableEntityList.push_back(new Wall(6*t, 9*t));
	DrawableEntityList.push_back(new Wall(6*t, 10*t));
	DrawableEntityList.push_back(new Wall(6*t, 11*t));
	DrawableEntityList.push_back(new Wall(6*t, 12*t));
	DrawableEntityList.push_back(new Wall(6*t, 13*t));
	DrawableEntityList.push_back(new Wall(6*t, 14*t));
	DrawableEntityList.push_back(new Wall(6*t, 15*t));
	DrawableEntityList.push_back(new Wall(6*t, 16*t));
	DrawableEntityList.push_back(new Wall(6*t, 17*t));
	DrawableEntityList.push_back(new Wall(6*t, 18*t));
	DrawableEntityList.push_back(new Wall(11*t, 4*t));
	DrawableEntityList.push_back(new Wall(12*t, 4*t));
	DrawableEntityList.push_back(new Wall(13*t, 4*t));
	DrawableEntityList.push_back(new Wall(14*t, 4*t));
	DrawableEntityList.push_back(new Wall(15*t, 4*t));
	DrawableEntityList.push_back(new Wall(15*t, 5*t));
	DrawableEntityList.push_back(new Wall(15*t, 6*t));
	DrawableEntityList.push_back(new Wall(15*t, 7*t));
	DrawableEntityList.push_back(new Wall(15*t, 8*t));
	DrawableEntityList.push_back(new Wall(15*t, 9*t));
	DrawableEntityList.push_back(new Wall(15*t, 10*t));
	DrawableEntityList.push_back(new Wall(15*t, 11*t));
	DrawableEntityList.push_back(new Wall(15*t, 12*t));
	DrawableEntityList.push_back(new Wall(15*t, 13*t));
	DrawableEntityList.push_back(new Wall(15*t, 14*t));
	DrawableEntityList.push_back(new Wall(15*t, 15*t));

	DrawableEntityList.push_back(new Wall(14*t, 10*t));
	DrawableEntityList.push_back(new Wall(14*t, 11*t));
	DrawableEntityList.push_back(new Wall(14*t, 12*t));
	DrawableEntityList.push_back(new Wall(14*t, 13*t));
	DrawableEntityList.push_back(new Wall(14*t, 14*t));
	DrawableEntityList.push_back(new Wall(14*t, 15*t));


	DrawableEntityList.push_back(hero);
	DrawableEntityList.push_back(pirate);
	DrawableEntityList.push_back(seven);
	for( int i = 0; i < numberOfObjects ; i++ )
		DrawableEntityList.push_back( arrayOfObjects[i] );
	for( int i = 0; i < NUM_OF_ENEMIES ; i++)
		DrawableEntityList.push_back(numbers[i]);
	std::cout << "DEL size: " << DrawableEntityList.size() << std::endl;

}

void GameState::UpdateSystem()
{
	GameEngine::getInstance()->ClearCollisionQuadtree();
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		DrawableEntityList[i]->UpdateSystem();
}

void GameState::Display()
{
	GameEngine::getInstance()->SetGameView();
	GameEngine::getInstance()->FlushRenderQueue();

	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		GameEngine::getInstance()->AddToRenderQueue(DrawableEntityList[i]);

	map->showMap(&GameEngine::getInstance()->getWindow(), hero->GetPosition());

	GameEngine::getInstance()->ExecuteRenderQueue();

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

void GameState::Cleanup()
{
	for ( unsigned int i = 0; i < DrawableEntityList.size(); i++ )
		delete DrawableEntityList[i];

	init = 0;
}
