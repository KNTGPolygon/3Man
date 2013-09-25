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

	wall[0] = new Wall(100, 100);
	wall[1] = new Wall(132, 100);
	wall[2] = new Wall(164, 100);
	wall[3] = new Wall(196, 100);
	wall[4] = new Wall(196, 116);
	wall[5] = new Wall(196, 132);
	wall[6] = new Wall(228, 132);
	wall[7] = new Wall(260, 132);
	wall[8] = new Wall(292, 132);
	wall[9] = new Wall(324, 132);

	DrawableEntityList.push_back(hero);
	DrawableEntityList.push_back(pirate);
	DrawableEntityList.push_back(seven);
	for( int i = 0; i < NUM_OF_ENEMIES ; i++)
		DrawableEntityList.push_back(numbers[i]);
	for ( int i = 0; i < 10; i++ )
		DrawableEntityList.push_back(wall[i]);
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
