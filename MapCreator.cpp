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

	//setting default value of camera
	cameraPosition.x = 350;
	cameraPosition.y = 200;

	toolboxFirstFieldNumber = 1;
	verticalToolboxFirstFieldNumber = 1;

}

void MapCreator::initializeMapArrays (int Size)
{
	//defining size of map
	this->Size = Size;

	//creating dynamic two-dimensional arrays
	createdMap = new Tile*[Size];
	for(unsigned int i = 0; i < Size; ++i)
    createdMap[i] = new Tile[Size];

	mapObjects = new MapObject*[Size*2];
	for(unsigned int i = 0; i < Size*2; ++i)
    mapObjects[i] = new MapObject[Size*2];

	//initialization of createdMap array (representation of created map) with first, default tile
	for(unsigned int row = 0; row < Size; row++)
	{
		for(unsigned int col = 0; col < Size; col++)
		{
			createdMap[row][col] = Tile(1,col*32 - 32, 48 + row*32);
		}
	}

	for(unsigned int row = 0; row < Size*2; row++)
		for(unsigned int col = 0; col < Size*2; col++)
		{
			mapObjects[row][col] = MapObject(-1,col*16 - 32, 48 + row*16);
		}

}

void MapCreator::Display(sf::RenderWindow *window)
{
	window->Clear();

	//counting from which field to draw
	unsigned int firstFieldX = 0;
	unsigned int firstFieldY = 0;

	firstFieldX = (unsigned int)(((cameraPosition.x - 400)>0?(cameraPosition.x-400):0)/sampleSpriteSize.x);
	firstFieldY = (unsigned int)(((cameraPosition.y - 240)>0?(cameraPosition.y-240):0)/sampleSpriteSize.y);

	//drawing createdMap graphical representation
	for(unsigned int row = firstFieldY; row < ((noOfTilesVisible.y + firstFieldY - 8)>Size? Size:(noOfTilesVisible.y + firstFieldY - 8)); row++)
	{
		for(unsigned int col = firstFieldX; col < ((noOfTilesVisible.x + firstFieldX - 1)>Size? Size:(noOfTilesVisible.x + firstFieldX - 1)); col++)
		{
			//drawing current field together with its frame
			sf::Vector2i temp = createdMap[row][col].getPosition();
			tileSprites.at(createdMap[row][col].getType()).SetPosition((float)temp.x, (float)temp.y);
			window->Draw(tileSprites.at(createdMap[row][col].getType()));
		}
	}

	
			for(unsigned int row = firstFieldY*2; row < ((noOfTilesVisible.y + firstFieldY - 8)*2 >Size*2? Size*2 :(noOfTilesVisible.y + firstFieldY - 8)*2); row++)
				{
					for(unsigned int col = firstFieldX*2; col < ((noOfTilesVisible.x + firstFieldX - 1)*2 >Size*2? Size*2:(noOfTilesVisible.x + firstFieldX - 1)*2); col++)
					{
						if(mapObjects[row][col].getType() > 0)
						{
							
							sf::Vector2i temp = mapObjects[row][col].getPosition();
							objectSprites.at(mapObjects[row][col].getType()).SetPosition((float)temp.x, (float)temp.y);
							window->Draw(objectSprites.at(mapObjects[row][col].getType()));
						}
					}
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
				objectSprites.at(toolboxIterator).SetScale(2,2);
				window->Draw(objectSprites.at(toolboxIterator));
				objectSprites.at(toolboxIterator).SetScale(0.5,0.5);

			}

			if(chosenObjectFromToolbox - verticalToolboxFirstFieldNumber + 1 > 0)
			{
				tileSprites.at(0).SetPosition(300 + cameraPosition.x, -270 + cameraPosition.y  + (chosenObjectFromToolbox - verticalToolboxFirstFieldNumber + 1)*96);
				tileSprites.at(0).SetScale(1,1);
				window->Draw(tileSprites.at(0));
				tileSprites.at(0).SetScale(0.5,0.5);
			}
			


}

bool MapCreator::LoadTileGraphics()
{
	int counter = 0;
	ImageManager* imgmng = ImageManager::getInstance();
	//creating map tiles (will be anchanced)
	std::string tileAddress = "Data/Textures/EditorMapTiles/";
	std::ifstream dataSet("Data/Textures/EditorMapTiles/EditorLoadingFile.txt");
	std::string str;

		 if (!dataSet) {
        std::cerr << "Nie udało się załadował pliku " <<" EditorLoadingFile.txt "<< "\n";
		return 0;
				 }

		 if(dataSet.good() == true)
		 {

			 //loading tileGraphics
		  while( !dataSet.eof() )
			{	
				dataSet >> str;
					if(str.at(0) == '-')
				{
					counter = 0;
					break;
				}
				
				
				tileGraphics[counter] = imgmng->loadImage(tileAddress + str);
				counter ++;
			
			 }

		 
		  tileAddress = "Data/Textures/MapObjects/";
		   //loading objectGraphics
		   while( !dataSet.eof() )
			{	
				dataSet >> str;
					if(str.at(0) == '-')
				{
					counter = 0;
					break;
				}
				
				objectGraphics[counter] = imgmng->loadImage(tileAddress + str);
				counter ++;
			
			 }
		   dataSet.close();
		 }
		  

	for(unsigned int i = 0; i < tileGraphics.size(); i++)
	{
		tileGraphics[i].CreateMaskFromColor(sf::Color(255,0,255));
	}


	for(unsigned int i = 0; i < objectGraphics.size(); i++)
	{
		objectGraphics[i].CreateMaskFromColor(sf::Color(255,0,255));
	}

	//here sprites are created
	CreateSprites();
	return 1;
}

void MapCreator::CreateSprites()
{
	//creating sprites for each available image in MapCreator
	sf::Sprite spr;
	for(unsigned int i = 0; i<tileGraphics.size();i++)
	{
		spr.SetImage(tileGraphics[i]);
		spr.SetScale(0.5,0.5);
		tileSprites.push_back(spr);
	}

	for(unsigned int i = 0; i<objectGraphics.size();i++)
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
		

		if(steering.GetMouseY() > 150 && steering.GetMouseX() < 680 && steering.IsKeyDown(sf::Key::LControl))
		{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();
			changingObjectInMap(mousePos);
		}
		else if(steering.GetMouseY() > 150 && steering.GetMouseX() < 680)
		{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();
			changingSpriteInMap(mousePos);
		}

	}

}

void MapCreator::GetTextboxEvent(sf::Event& event, std::string text, CreatorStates &state)
{
	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Return) && state == SET_MAP_SIZE)
	{
		int x = atoi(text.c_str());
		if (x <= 0)
		{
			std::cout << " This size is <= 0, which is wrong! Setting to 32" << std::endl;
			x = 32;
		}
		if (x>256)
			{
				std::cout << " Size too big! Over 256! Setting to default 256 " << std::endl;
				x = 256;
			}
		initializeMapArrays(x);
		state = MAIN;
	}
}

void MapCreator::GetEvent(sf::Event& event)
{
	sf::Vector2i mousePos;
	mousePos.x = steering.GetMouseX();
	mousePos.y = steering.GetMouseY();

	if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::F2))
	{
		saveMap("Test");
	}

	else if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::D) )
	{
		if(toolboxFirstFieldNumber > 1)
			toolboxFirstFieldNumber --;
	}

	else if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::A) )
	{
		if(toolboxFirstFieldNumber < tileSprites.size())
			toolboxFirstFieldNumber ++;
	}

	else if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::S) )
	{
		if(verticalToolboxFirstFieldNumber > 1)
			verticalToolboxFirstFieldNumber --;
	}

	else if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::W) )
	{
		if(verticalToolboxFirstFieldNumber < objectSprites.size())
			verticalToolboxFirstFieldNumber ++;
	}

	else if((event.Type == sf::Event::MouseButtonPressed) && (event.Key.Code == sf::Mouse::Left))
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

	noOfTilesVisible.x = (int)(SCREEN_WIDTH/sampleSpriteSize.x);
	noOfTilesVisible.y = (int)(SCREEN_WIDTH/sampleSpriteSize.y);

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
	for(unsigned int rectangleCheckIterator = 1; rectangleCheckIterator <= toolboxRectangles.size(); rectangleCheckIterator++)
	{
		if(toolboxRectangles[rectangleCheckIterator].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			unsigned int tempCheck = rectangleCheckIterator + (toolboxFirstFieldNumber - 1);
			if(tempCheck >= 1 && tempCheck < tileSprites.size())
			{
				chosenTileFromToolbox = tempCheck;
			}
		}
	}

	if(toolboxClickPosition.x > 700)
	for(unsigned int rectangleCheckIterator = 1; rectangleCheckIterator <= toolboxVerticalRectangles.size(); rectangleCheckIterator++)
	{
		if(toolboxVerticalRectangles[rectangleCheckIterator].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			unsigned int tempCheck = rectangleCheckIterator + (verticalToolboxFirstFieldNumber - 1);
			
			if(tempCheck >= 1 && tempCheck < objectSprites.size())
			{
				chosenObjectFromToolbox = tempCheck;	
			}
		}
	}
}


void MapCreator::changingSpriteInMap(sf::Vector2i mapClickPosition)
{
	sf::Vector2i realClickPosition;
	realClickPosition.x = (int)(cameraPosition.x - 370 + mapClickPosition.x);
	realClickPosition.y = (int)(cameraPosition.y - 350 + mapClickPosition.y);
	if(realClickPosition.x > 0 && realClickPosition.y > 0 && chosenTileFromToolbox != 0 && (unsigned int)(realClickPosition.x/32) < Size && (unsigned int)(realClickPosition.y/32) <Size)
	{
		createdMap[realClickPosition.y/32][realClickPosition.x/32].changeType(chosenTileFromToolbox);
	}

}

void MapCreator::changingObjectInMap(sf::Vector2i mapClickPosition)
{
	sf::Vector2i realClickPosition;
	realClickPosition.x = (int)(cameraPosition.x - 370 + mapClickPosition.x);
	realClickPosition.y = (int)(cameraPosition.y - 350 + mapClickPosition.y);
	if(realClickPosition.x > 0 && realClickPosition.y > 0 && chosenObjectFromToolbox >0 && (unsigned int)(realClickPosition.x/16) < Size*2 && (unsigned int)(realClickPosition.y/16) <Size*2)
	{
		mapObjects[realClickPosition.y/16][realClickPosition.x/16].changeType(chosenObjectFromToolbox);
	}

}
 

MapCreator::~MapCreator()
{
	
	if(createdMap != NULL)
	{
	for(unsigned int i = 0; i < Size; ++i)
    delete [] createdMap[i];
	delete [] createdMap;


	for(unsigned int i = 0; i < Size; ++i)
    delete mapObjects[i];
	delete mapObjects;
	}

	 delete blackHorizontalImage;
	 delete blackHorizontalSprite;
	 delete blackVerticalImage;
	 delete blackVerticalSprite;

}

bool MapCreator::saveMap(std::string filename)
{
	int counter = 0;
	std::stringstream tempFilename;

	std::string path = "./Data/Maps/";
	std::ofstream outputFile;

	//opening dataSet!
	std::ifstream dataSet("Data/Textures/EditorMapTiles/EditorLoadingFile.txt");
	std::string str;

		 if (!dataSet) 
			 {
				std::cerr << "Nie udało się załadował pliku " <<" EditorLoadingFile.txt "<< "\n";
				return 0;
			 }
		
			tempFilename << filename << ".map";

	
	outputFile.open((path + tempFilename.str()).c_str());

	//to skip border image address
	dataSet >> str;

	if(outputFile)
	{
		outputFile << Size << "\n" << "*" << "\n";
		outputFile << "./Data/Textures/MapTiles/" << "\n" << "*" << "\n";
			
				  while( !dataSet.eof() )
					{	
						dataSet >> str;
							if(str.at(0) == '-')
						{
							
							break;
						}

						outputFile << str << "\n";

				   }
		outputFile << "*" << "\n";

		//skipping blank object
		dataSet >> str;

		//saving info about objects into map file
		while( !dataSet.eof() )
					{	
						dataSet >> str;
							if(str.at(0) == '-')
						{
							break;
						}

						outputFile << str << "\n";

				   }

		outputFile << "*" << "\n";

		for(unsigned int row = 0; row < Size; row++)
		{
			for(unsigned int col = 0; col < Size ; col++)
			{
				if(col != Size-1)
					outputFile << createdMap[row][col].getType() << " ";
				else
				{
					outputFile << createdMap[row][col].getType();
				}
			}
			outputFile << "\n" ;
		}
		outputFile << "*" << "\n";

		for(unsigned int row = 0; row < Size*2; row++)
			{
				for(unsigned int col = 0; col < Size*2; col++)
				{
					if(col != Size*2-1 && mapObjects[row][col].getType() != -1)
						outputFile << " " << mapObjects[row][col].getType() << " ";
					else if(col != Size*2-1)
					{
						outputFile << mapObjects[row][col].getType() << " ";
					}
					else if(mapObjects[row][col].getType() != -1)
					{
						outputFile << " " << mapObjects[row][col].getType();
					}
					else
					{
						outputFile << mapObjects[row][col].getType();
					}
				}
				outputFile << "\n" ;
			}
		outputFile << "*" ;
		std::cout << "Map saved!" << std::endl;
	}

	outputFile.close();
	return true;
}