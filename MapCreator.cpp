#include "MapCreator.h"

MapCreator::MapCreator(const sf::Input &_steering)
	:steering(_steering)
{
	//loading images from files, creating sprites
	LoadTileGraphics();
	blackHorizontalImage = new sf::Image();
	blackVerticalImage = new sf::Image();

	blackHorizontalImage->Create(800,120,sf::Color(0,0,0,255));
	blackVerticalImage->Create(120,800,sf::Color(0,0,0,255));

	blackHorizontalSprite = new sf::Sprite();
	blackVerticalSprite = new sf::Sprite();

	blackHorizontalSprite->SetImage(*blackHorizontalImage);
	blackVerticalSprite->SetImage(*blackVerticalImage);
	
	chosenTileFromToolbox = 0;
	chosenObjectFromToolbox = 0;
	
	sampleSpriteSize = tileSprites.at(1).GetSize();

	//defining size of map
	Size = 30;

	//setting default value of camera
	cameraPosition.x = 350;
	cameraPosition.y = 200;

	toolboxFirstFieldNumber = 1;
	verticalToolboxFirstFieldNumber = 1;

	//creating dynamic two-dimensional arrays
	createdMap = new Tile*[Size];
	for(int i = 0; i < Size; ++i)
    createdMap[i] = new Tile[Size];

	map_data = new MapObject*[Size*2];
	for(int i = 0; i < Size; ++i)
    map_data[i] = new MapObject[Size*2];

	//initialization of createdMap array (representation of created map) with first, default tile
	for(int row = 0; row < Size; row++)
	{
		for(int col = 0; col < Size; col++)
		{
			createdMap[row][col] = Tile(1,col*32 - 32, 48 + row*32);
		}
	}

	for(int row = 0; row < Size; row++)
		for(int col = 0; col < Size; col++)
		{
			map_data[row][col] = MapObject(0,col*16 - 32, 48 + row*16);
		}

}


void MapCreator::Display(sf::RenderWindow *window)
{
	window->Clear();

	//counting from which field to draw
	unsigned int firstFieldX = 0;
	unsigned int firstFieldY = 0;

	firstFieldX = ((cameraPosition.x - 400)>0?(cameraPosition.x-400):0)/sampleSpriteSize.x;
	firstFieldY = ((cameraPosition.y - 240)>0?(cameraPosition.y-240):0)/sampleSpriteSize.y;

	//drawing createdMap graphical representation
	for(int row = firstFieldY; row < ((noOfTilesVisible.y + firstFieldY - 8)>Size? Size:(noOfTilesVisible.y + firstFieldY - 8)); row++)
		for(int col = firstFieldX; col < ((noOfTilesVisible.x + firstFieldX - 1)>Size? Size:(noOfTilesVisible.x + firstFieldX - 1)); col++)
		{
			//drawing current field together with its frame
			sf::Vector2i temp = createdMap[row][col].getPosition();
			tileSprites.at(createdMap[row][col].getType()).SetPosition(temp.x, temp.y);
			window->Draw(tileSprites.at(createdMap[row][col].getType()));
		}

		//checking whether there are 8 more sprites to draw in horizontal toolbox, else get number of last field
		int lastField;
		if(toolboxFirstFieldNumber + 8 > tileSprites.size())
		{
			lastField = tileSprites.size();
		}
		else
		{
			lastField = toolboxFirstFieldNumber + 8;
		}

		//setting positions of black toolbox-fields
		blackHorizontalSprite->SetPosition(cameraPosition.x-400, cameraPosition.y-300);
		blackVerticalSprite->SetPosition(cameraPosition.x+280, cameraPosition.y - 300);

		//drawing black toolbox-fields
		window->Draw(*blackHorizontalSprite);
		window->Draw(*blackVerticalSprite);

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
		}


		//--------------------

		if(verticalToolboxFirstFieldNumber + 5 > objectSprites.size())
		{
			lastField = objectSprites.size();
		}
		else
		{
			lastField = verticalToolboxFirstFieldNumber + 5;
		}

		for(int toolboxIterator = verticalToolboxFirstFieldNumber;toolboxIterator < lastField; toolboxIterator ++ )
		{
			objectSprites.at(toolboxIterator).SetPosition(300 + cameraPosition.x , -270 + cameraPosition.y + (toolboxIterator - verticalToolboxFirstFieldNumber + 1)*96);
			window->Draw(objectSprites.at(toolboxIterator));

		}

		if(chosenObjectFromToolbox - verticalToolboxFirstFieldNumber + 1 > 0 )
		{
			tileSprites.at(0).SetPosition(300 + cameraPosition.x, -270 + cameraPosition.y  + (chosenObjectFromToolbox - verticalToolboxFirstFieldNumber + 1)*96);
			tileSprites.at(0).SetScale(1,1);
			window->Draw(tileSprites.at(0));
			tileSprites.at(0).SetScale(0.5,0.5);	
		}

	
}

void MapCreator::LoadTileGraphics()
{
	//creating map tiles (will be anchanced)
	ImageManager* imgmng = ImageManager::getInstance();
	std::string tileAddress = "Data/Textures/EditorMapTiles/";
	tileGraphics[0] = imgmng->loadImage(tileAddress + "border.png");
	tileGraphics[1] = imgmng->loadImage(tileAddress + "grass.png");
	tileGraphics[2] = imgmng->loadImage(tileAddress + "lava.png");
	tileGraphics[3] = imgmng->loadImage(tileAddress + "pinky.png");
	tileGraphics[4] = imgmng->loadImage(tileAddress + "wall.png");
	tileGraphics[5] = imgmng->loadImage(tileAddress + "water.png");
	tileGraphics[6] = imgmng->loadImage(tileAddress + "border.png");
	tileGraphics[7] = imgmng->loadImage(tileAddress + "grass.png");
	tileGraphics[8] = imgmng->loadImage(tileAddress + "lava.png");
	tileGraphics[9] = imgmng->loadImage(tileAddress + "pinky.png");
	tileGraphics[10] = imgmng->loadImage(tileAddress + "wall.png");
	tileGraphics[11] = imgmng->loadImage(tileAddress + "water.png");

	for(int i = 0; i < tileGraphics.size(); i++)
	{
		tileGraphics[i].CreateMaskFromColor(sf::Color(255,0,255));
	}

	tileAddress = "Data/Textures/MapObjects/";
	objectGraphics[0] = imgmng->loadImage(tileAddress + "Blank.png");
	objectGraphics[1] = imgmng->loadImage(tileAddress + "Star.png");
	objectGraphics[2] = imgmng->loadImage(tileAddress + "Square.png");
	objectGraphics[3] = imgmng->loadImage(tileAddress + "Pentagon.png");
	objectGraphics[4] = imgmng->loadImage(tileAddress + "Cloud.png");
	objectGraphics[5] = imgmng->loadImage(tileAddress + "Circle.png");
	objectGraphics[6] = imgmng->loadImage(tileAddress + "Arrow.png");
	objectGraphics[7] = imgmng->loadImage(tileAddress + "Triangle.png");

	for(int i = 0; i < objectGraphics.size(); i++)
	{
		objectGraphics[i].CreateMaskFromColor(sf::Color(255,0,255));
	}

	//here sprites are created
	CreateSprites();
}

void MapCreator::CreateSprites()
{
	//creating sprites for each available image in MapCreator
	sf::Sprite spr;
	for(int i = 0; i<tileGraphics.size();i++)
	{
		spr.SetImage(tileGraphics[i]);
		spr.SetScale(0.5,0.5);
		tileSprites.push_back(spr);
	}

	for(int i = 0; i<objectGraphics.size();i++)
	{
		spr.SetImage(objectGraphics[i]);
		spr.SetScale(1,1);
		objectSprites.push_back(spr);
	}

}

void MapCreator::GetSteeringEvent()
{
	
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

	if(steering.IsMouseButtonDown(sf::Mouse::Left))
	{
		if(steering.GetMouseY() > 150 && steering.GetMouseX() < 680)
		{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();
			changingSpriteInMap(mousePos);
		}

	}

}

void MapCreator::GetEvent(sf::Event& event)
{
	sf::Vector2i mousePos;
	mousePos.x = steering.GetMouseX();
	mousePos.y = steering.GetMouseY();

	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::D) )
	{
		if(toolboxFirstFieldNumber > 1)
			toolboxFirstFieldNumber --;
	}

	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::A) )
	{
		if(toolboxFirstFieldNumber < tileSprites.size())
			toolboxFirstFieldNumber ++;
	}

	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::S) )
	{
		if(verticalToolboxFirstFieldNumber > 1)
			verticalToolboxFirstFieldNumber --;
	}

	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::W) )
	{
		if(verticalToolboxFirstFieldNumber < objectSprites.size())
			verticalToolboxFirstFieldNumber ++;
	}

	if((event.Type == sf::Event::MouseButtonPressed) && (event.Key.Code == sf::Mouse::Left))
	{
		if(mousePos.y < 100 || mousePos.x > 700)
		{
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
	int numberOfToolboxVerticalRectangles = (int)((SCREEN_HEIGHT-160)/80);

	for(int rectangleCreator = 1; rectangleCreator <= numberOfToolboxRectangles ; rectangleCreator ++)
	{
		toolboxRectangles[rectangleCreator] = sf::IntRect (20 + (rectangleCreator - 1)*96 , 20, 84 + (rectangleCreator - 1)*96 , 84);
	}

	for(int rectangleCreator = 1; rectangleCreator <= numberOfToolboxVerticalRectangles ; rectangleCreator ++)
	{
		toolboxVerticalRectangles[rectangleCreator] = sf::IntRect (700, 125 + (rectangleCreator - 1)*96, 764 , 189 + (rectangleCreator - 1)*96);
	}

}

void MapCreator::toolboxManagement(sf::Vector2i toolboxClickPosition)
{
	if(toolboxClickPosition.y < 100)
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

	if(toolboxClickPosition.x > 700)
	for(int rectangleCheckIterator = 1; rectangleCheckIterator <= toolboxVerticalRectangles.size(); rectangleCheckIterator++)
	{
		if(toolboxVerticalRectangles[rectangleCheckIterator].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			int tempCheck = rectangleCheckIterator + (verticalToolboxFirstFieldNumber - 1);
			
			if(tempCheck >= 1 && tempCheck < objectSprites.size())
			{
				chosenObjectFromToolbox = tempCheck;	
				std::cout << chosenObjectFromToolbox << std::endl;
			}
		}
	}
}


void MapCreator::changingSpriteInMap(sf::Vector2i mapClickPosition)
{
	sf::Vector2i realClickPosition;
	realClickPosition.x = cameraPosition.x - 370 + mapClickPosition.x;
	realClickPosition.y = cameraPosition.y - 350 + mapClickPosition.y;
	if(realClickPosition.x > 0 && realClickPosition.y > 0 && chosenTileFromToolbox != 0 && (realClickPosition.x/32) < Size && (realClickPosition.y/32) <Size)
	{
		createdMap[realClickPosition.y/32][realClickPosition.x/32].changeType(chosenTileFromToolbox);
	}

}

MapCreator::~MapCreator()
{
	delete blackHorizontalImage;
	delete blackVerticalImage;
	delete blackHorizontalSprite;
	delete blackVerticalSprite;

	for ( int i = 0; i < Size; ++i )
		delete[] createdMap[i];
	delete[] createdMap;
}
 
