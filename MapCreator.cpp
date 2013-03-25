#include "MapCreator.h"

MapCreator::MapCreator(const sf::Input &_steering)
	:steering(_steering),state(CHOOSING_ARRAY), cooldown(0)
{
	//loading images from files, creating sprites
	LoadTileGraphics();
	blackImage = new sf::Image();
	blackImage->Create(800,120,sf::Color(0,0,0,255));
	blackSprite = new sf::Sprite();
	blackSprite->SetImage(*blackImage);

	chosenTileFromToolbox = 0;
	

	sampleSpriteSize = tileSprites.at(1).GetSize();


	//defining size of map
	Size = 30;

	//setting default value of camera
	cameraPosition.x = 350;
	cameraPosition.y = 200;

	toolboxFirstFieldNumber = 1;

	//creating dynamic two-dimensional array
	createdMap = new Tile*[Size];
	for(int i = 0; i < Size; ++i)
    createdMap[i] = new Tile[Size];

	//initialization of createdMap array (representation of created map) with first, default tile
	for(int row = 0; row < Size; row++)
		for(int col = 0; col < Size; col++)
		{
			createdMap[row][col] = Tile(1,col*32 - 32, 48 + row*32);
		}

}


void MapCreator::Display(sf::RenderWindow *window)
{
	//reseting clock, needed for events
	clock.Reset();
	window->Clear();

	//counting from which field to draw
	unsigned int firstFieldX = 0;
	unsigned int firstFieldY = 0;

	firstFieldX = ((cameraPosition.x - 400)>0?(cameraPosition.x-400):0)/sampleSpriteSize.x;
	firstFieldY = ((cameraPosition.y - 240)>0?(cameraPosition.y-240):0)/sampleSpriteSize.y;

	//std::cout << Size << " -- " << noOfTilesVisible.x << " -- " << noOfTilesVisible.y << std::endl;
	//drawing createdMap graphical representation
	for(int row = firstFieldY; row < ((noOfTilesVisible.y + firstFieldY + 2)>Size? Size:(noOfTilesVisible.y + firstFieldY + 2)); row++)
		for(int col = firstFieldX; col < ((noOfTilesVisible.x + firstFieldX + 2)>Size? Size:(noOfTilesVisible.x + firstFieldX + 2)); col++)
		{
			//drawing current field together with its frame
			sf::Vector2i temp = createdMap[row][col].getPosition();
			tileSprites.at(createdMap[row][col].getType()).SetPosition(temp.x, temp.y);
			tileSprites.at(0).SetPosition(temp.x, temp.y);
			window->Draw(tileSprites.at(createdMap[row][col].getType()));
			window->Draw(tileSprites.at(0));
		}

		

		//checking whether there are 5 more sprites to draw in toolbox, else get number of last field
		int lastField;
		if(toolboxFirstFieldNumber + 8 > tileSprites.size())
		{
			lastField = tileSprites.size();
		}
		else
		{
			lastField = toolboxFirstFieldNumber + 8;
		}


		blackSprite->SetPosition(cameraPosition.x-400, cameraPosition.y-300);
		window->Draw(*blackSprite);

		for(int toolboxIterator = toolboxFirstFieldNumber;toolboxIterator < lastField; toolboxIterator ++ )
		{
			tileSprites.at(toolboxIterator).SetPosition(-380 + cameraPosition.x + (toolboxIterator-toolboxFirstFieldNumber)*96, -280 + cameraPosition.y);
			//toolbox has full sized field-sprites
			tileSprites.at(toolboxIterator).SetScale(1,1);
			window->Draw(tileSprites.at(toolboxIterator));
			//changing sprites size to default for map-drawing
			tileSprites.at(toolboxIterator).SetScale(0.5,0.5);
		}

		if(chosenTileFromToolbox - toolboxFirstFieldNumber + 1 > 0 )
		{
			tileSprites.at(0).SetPosition(-380 + cameraPosition.x + (chosenTileFromToolbox - toolboxFirstFieldNumber)*96, -280 + cameraPosition.y);
			tileSprites.at(0).SetScale(1,1);
			window->Draw(tileSprites.at(0));
				tileSprites.at(0).SetScale(0.5,0.5);
			//	std::cout << cameraPosition.x <<  " -- " <<  cameraPosition.y << std::endl;
		}

	
}

void MapCreator::LoadTileGraphics()
{
	//creating map tiles (will be anchanced)
	tileGraphics[0] = Tile(0,"Data/Textures/border.png");
	tileGraphics[1] = Tile(1,"Data/Textures/grass.png");	
	tileGraphics[2] = Tile(2,"Data/Textures/lava.png");
	tileGraphics[3] = Tile(3,"Data/Textures/pinky.png");
	tileGraphics[4] = Tile(4,"Data/Textures/wall.png");
	tileGraphics[5] = Tile(5,"Data/Textures/water.png");
	tileGraphics[6] = Tile(6,"Data/Textures/border.png");
	tileGraphics[7] = Tile(7,"Data/Textures/grass.png");	
	tileGraphics[8] = Tile(8,"Data/Textures/lava.png");
	tileGraphics[9] = Tile(9,"Data/Textures/pinky.png");
	tileGraphics[10] = Tile(10,"Data/Textures/wall.png");
	tileGraphics[11] = Tile(11,"Data/Textures/water.png");
	//here sprites are created
	CreateSprites();
}

void MapCreator::CreateSprites()
{
	//creating sprites for each available image in MapCreator
	sf::Sprite spr;
	for(int i = 0; i<tileGraphics.size();i++)
	{
		spr.SetImage(tileGraphics[i].tileTexture);
		spr.SetScale(0.5,0.5);
		tileSprites.push_back(spr);
	}
}

void MapCreator::GetSteeringEvent()
{
	
	//checking events with cooldown included (so each button pressed will surely count as 1)
	if( steering.IsKeyDown( sf::Key::Right ) ){
				
		cameraPosition.x += 20;
		}

	if( steering.IsKeyDown( sf::Key::Left ) && cameraPosition.x > 360 ){
				
		cameraPosition.x -= 20;
		}

	if( steering.IsKeyDown( sf::Key::Up ) && cameraPosition.y > 200 ){
				
		cameraPosition.y -= 20;
		}

	if( steering.IsKeyDown( sf::Key::Down ) ){
				
		cameraPosition.y += 20;
		}

	//if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Mouse::Left))
	if(steering.IsMouseButtonDown(sf::Mouse::Left))
	{
		if(steering.GetMouseY() > 100)
		{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();
			changingSpriteInMap(mousePos);
		}

	}

}

void MapCreator::GetEvent(sf::Event event)
{
	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::A) )
	{
		if(toolboxFirstFieldNumber > 1)
			toolboxFirstFieldNumber --;
		cooldown = 0.1;
	}
	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::D) )
	{
		if(toolboxFirstFieldNumber < tileSprites.size())
			toolboxFirstFieldNumber ++;
		cooldown = 0.1;
	}

	if((event.Type == sf::Event::MouseButtonPressed) && (event.Key.Code == sf::Mouse::Left))
	//if(true)
	{
		if(steering.GetMouseY() < 100)
		{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();

			toolboxManagement(mousePos);
		}

	}

	

}

void MapCreator::MoveCamera(sf::View *View, sf::RenderWindow *window)
{
	View->SetHalfSize((float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT/2); 
	View->SetCenter(cameraPosition);
	window->SetView(*View);
}	

void MapCreator::GetScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	SCREEN_WIDTH  = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;

	noOfTilesVisible.x = SCREEN_WIDTH/sampleSpriteSize.x;
	noOfTilesVisible.y = SCREEN_WIDTH/sampleSpriteSize.y;

	int numberOfToolboxRectangles = (int)((SCREEN_WIDTH-20)/96);

	for(int rectangleCreator = 1; rectangleCreator <= numberOfToolboxRectangles ; rectangleCreator ++)
	{
		toolboxRectangles[rectangleCreator] = sf::IntRect (20 + (rectangleCreator - 1)*96 , 20, 84 + (rectangleCreator - 1)*96 , 84);
	}

}

void MapCreator::toolboxManagement(sf::Vector2i toolboxClickPosition)
{
	for(int rectangleCheckIterator = 1; rectangleCheckIterator <= toolboxRectangles.size(); rectangleCheckIterator++)
	{
		if(toolboxRectangles[rectangleCheckIterator].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			int tempCheck = rectangleCheckIterator + (toolboxFirstFieldNumber - 1);
			if(tempCheck >= 1 && tempCheck < tileSprites.size())
			{
				chosenTileFromToolbox = tempCheck;
			}
		}
	}
}


void MapCreator::changingSpriteInMap(sf::Vector2i mapClickPosition)
{
	//std::cout << cameraPosition.x - 370 + mapClickPosition.x << " -- " << cameraPosition.y - 350 + mapClickPosition.y << std::endl;
	sf::Vector2i realClickPosition;
	realClickPosition.x = cameraPosition.x - 370 + mapClickPosition.x;
	realClickPosition.y = cameraPosition.y - 350 + mapClickPosition.y;
	if(realClickPosition.x > 0 && realClickPosition.y > 0 && chosenTileFromToolbox != 0 && (realClickPosition.x/32) < Size && (realClickPosition.y/32) <Size)
	{
		createdMap[realClickPosition.y/32][realClickPosition.x/32].changeType(chosenTileFromToolbox);
		//std::cout << realClickPosition.y << " -- "  << realClickPosition.x<< std::endl;
	}


}