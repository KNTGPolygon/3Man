#include "MapCreator.h"

MapCreator::MapCreator(const sf::Input &_steering)
	:steering(_steering)
{

	toolboxMenuState = SUBMENU_CHOICE;

	for(int i = 0; i < 10; i++)
	{
		hotKeys[i] = 0;
	}
	lControlPressed = false;

	//loading images from files, creating sprites
	LoadTileGraphics();

	blackBackgroundShape = sf::Shape::Rectangle(-64,-20,800,40, sf::Color(0,0,0,255));
	
	chosenTileFromToolbox = 0;
	chosenObjectFromToolbox = 0;
	
	//setting default value of camera
	cameraPosition.x = 350;
	cameraPosition.y = 200;

	toolboxFirstFieldNumber = 1;

	whichSubmenuButtonAnimate = -1;
	//creating rectangles for buttons in main toolbar-menu
	submenuButtonRectangles[0] = sf::IntRect(30,20,130,120);
	submenuButtonRectangles[1] = sf::IntRect(150,20,250,120);
	submenuButtonRectangles[2] = sf::IntRect(270,20,370,120);
	submenuButtonRectangles[3] = sf::IntRect(390,20,490,120);

	//creating rectangle for return button
	submenuReturnButtonRectangle = sf::IntRect(695, 20, 755, 120);

}

void MapCreator::initializeMapArrays (unsigned int Size)
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

	firstFieldX = (unsigned int)(((cameraPosition.x - 400)>0?(cameraPosition.x-400):0)/32);
	firstFieldY = (unsigned int)(((cameraPosition.y - 240)>0?(cameraPosition.y-240):0)/32);

	//----------------------------- MAP DISPLAY (TILES & OBJECTS)  ------------------------------------------
	for(unsigned int row = firstFieldY; row < ((noOfTilesVisible.y + firstFieldY - 8)>Size? Size:(noOfTilesVisible.y + firstFieldY - 8)); row++)
	{
		for(unsigned int col = firstFieldX; col < ((noOfTilesVisible.x + firstFieldX + 2)>Size? Size:(noOfTilesVisible.x + firstFieldX + 2)); col++)
		{
			//drawing current field together with its frame
			sf::Vector2i temp = createdMap[row][col].getPosition();
			tileSprites.at(createdMap[row][col].getType()).SetPosition((float)temp.x, (float)temp.y);
			window->Draw(tileSprites.at(createdMap[row][col].getType()));
		}
	}

	
			for(unsigned int row = firstFieldY*2; row < ((noOfTilesVisible.y + firstFieldY - 8)*2 >Size*2? Size*2 :(noOfTilesVisible.y + firstFieldY - 8)*2); row++)
				{
					for(unsigned int col = firstFieldX*2; col < ((noOfTilesVisible.x + firstFieldX + 1)*2 >Size*2? Size*2:(noOfTilesVisible.x + firstFieldX + 1)*2); col++)
					{
						if(mapObjects[row][col].getType() > 0)
						{
							
							sf::Vector2i temp = mapObjects[row][col].getPosition();
							objectSprites.at(mapObjects[row][col].getType()).SetPosition((float)temp.x, (float)temp.y);
							window->Draw(objectSprites.at(mapObjects[row][col].getType()));
						}
					}
				}


				//Drawing black toolbox field
				window->Draw(blackBackgroundShape);

		//----------------------------- MAIN EDITOR MENU DISPLAY ------------------------------------------
			if(toolboxMenuState == SUBMENU_CHOICE)
			{
				//counting camera's position according to default,beginning point to draw submenu buttons in the right place
				int deltaCamPosX = (int)(cameraPosition.x - 350);
				int deltaCamPosY = (int)(cameraPosition.y - 200);

				submenuButtonSprite[0]->SetPosition((float)(-20 + deltaCamPosX),(float)(-80 + deltaCamPosY));			
				submenuButtonSprite[1]->SetPosition((float)(100 + deltaCamPosX),(float)(-80 + deltaCamPosY));
				submenuButtonSprite[2]->SetPosition((float)(220 + deltaCamPosX),(float)(-80 + deltaCamPosY));
				submenuButtonSprite[3]->SetPosition((float)(340 + deltaCamPosX),(float)(-80 + deltaCamPosY));
				window->Draw(*submenuButtonSprite[0]);
				window->Draw(*submenuButtonSprite[1]);
				window->Draw(*submenuButtonSprite[2]);
				window->Draw(*submenuButtonSprite[3]);

				if(whichSubmenuButtonAnimate != -1)
				{
					submenuButtonSprite[4]->SetPosition(submenuButtonSprite[whichSubmenuButtonAnimate]->GetPosition());
					window->Draw(*submenuButtonSprite[4]);
					whichSubmenuButtonAnimate = -1;

				}
			}
	//----------------------------- GROUNDS DISPLAY ------------------------------------------
			else if (toolboxMenuState == GROUNDS)
			{

				//checking whether there are 7 more sprites to draw in horizontal toolbox, else get number of last field
				int lastField;
				if(toolboxFirstFieldNumber + 7 > tileSprites.size())
				{
					lastField = tileSprites.size();
				}
				else
				{
					lastField = toolboxFirstFieldNumber + 7;
				}

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

			}

			//----------------------------- OBJECTS DISPLAY ------------------------------------------
			else if (toolboxMenuState == OBJECTS)
			{

				int lastField;
				if(toolboxFirstFieldNumber + 7 > objectSprites.size())
				{
					lastField = objectSprites.size();
				}
				else
				{
					lastField = toolboxFirstFieldNumber + 7;
				}

				for(int toolboxIterator = toolboxFirstFieldNumber;toolboxIterator < lastField; toolboxIterator ++ )
				{
					objectSprites.at(toolboxIterator).SetPosition(-380 + cameraPosition.x + (toolboxIterator-toolboxFirstFieldNumber)*96, -280 + cameraPosition.y);
					objectSprites.at(toolboxIterator).SetScale(2,2);
					window->Draw(objectSprites.at(toolboxIterator));
					//changing sprites size to default for map-drawing
					objectSprites.at(toolboxIterator).SetScale(0.5,0.5);
				}
		

				if(chosenObjectFromToolbox - toolboxFirstFieldNumber + 1 > 0 )
				{
					tileSprites.at(0).SetPosition(-380 + cameraPosition.x + (chosenObjectFromToolbox - toolboxFirstFieldNumber)*96, -280 + cameraPosition.y);
					tileSprites.at(0).SetScale(1,1);
					window->Draw(tileSprites.at(0));
					tileSprites.at(0).SetScale(0.5,0.5);	
				}

			}


			//-------------------- ANIMATING MAIN MENU BUTTONS ------------------------------------
			if(toolboxMenuState != SUBMENU_CHOICE)
			{
				submenuButtonSprite[5]->SetPosition(-380 + cameraPosition.x + 7 * 96, -280 + cameraPosition.y);
				window->Draw(*submenuButtonSprite[5]);
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
				getline (dataSet,str);

				//reading paths and ignoring everything after space
				std::istringstream iss(str);
				iss >> str;
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

	submenuButtonImage[0] = imgmng->loadImage("Data/Textures/Buttons/Tiles.bmp");
	submenuButtonImage[1] = imgmng->loadImage("Data/Textures/Buttons/Objects.bmp");
	submenuButtonImage[2] = imgmng->loadImage("Data/Textures/Buttons/Enemies.bmp");
	submenuButtonImage[3] = imgmng->loadImage("Data/Textures/Buttons/Save.bmp");
	submenuButtonImage[4] = imgmng->loadImage("Data/Textures/Buttons/ButtonFocus.bmp");
	submenuButtonImage[5] = imgmng->loadImage("Data/Textures/Buttons/Back.bmp");

	for(int i = 0; i < 6; i++)
	{
		submenuButtonImage[i].CreateMaskFromColor(sf::Color (255,0,255));
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
		spr.SetScale(0.5,0.5);
		objectSprites.push_back(spr);
	}

	for(int i = 0; i < 6; i++)
	{
	submenuButtonSprite[i] = new sf::Sprite();
	submenuButtonSprite[i]->SetImage(submenuButtonImage[i]);
	submenuButtonSprite[i]->SetScale(1,1);
	}

}

void MapCreator::GetSteeringEvent()
{
	
	if( steering.IsKeyDown( sf::Key::Right ) ){
				
		cameraPosition.x += 20;
		blackBackgroundShape.Move(20,0);
		}

	if( steering.IsKeyDown( sf::Key::Left ) && cameraPosition.x > 360 ){
				
		cameraPosition.x -= 20;
		blackBackgroundShape.Move(-20,0);
		}

	if( steering.IsKeyDown( sf::Key::Up ) && cameraPosition.y > 200 ){
				
		cameraPosition.y -= 20;
		blackBackgroundShape.Move(0,-20);
		}

	if( steering.IsKeyDown( sf::Key::Down ) ){
				
		cameraPosition.y += 20;
		blackBackgroundShape.Move(0,20);
		}


		//!!!!!!!!!!!!!
	int mousePositionX = steering.GetMouseX();
	int mousePositionY = steering.GetMouseY();

	if(mousePositionY < 120 && toolboxMenuState == SUBMENU_CHOICE)
	{
		if(submenuButtonRectangles[0].Contains(steering.GetMouseX(), steering.GetMouseY()))
		{
			whichSubmenuButtonAnimate = 0;
		}

		else if(submenuButtonRectangles[1].Contains(steering.GetMouseX(), steering.GetMouseY()))
		{
			whichSubmenuButtonAnimate = 1;
		}

		else if(submenuButtonRectangles[2].Contains(steering.GetMouseX(), steering.GetMouseY()))
		{
			whichSubmenuButtonAnimate = 2;
		}

		else if(submenuButtonRectangles[3].Contains(steering.GetMouseX(), steering.GetMouseY()))
		{
			whichSubmenuButtonAnimate = 3;
		}
	}

	if(steering.IsMouseButtonDown(sf::Mouse::Left))
	{
		

		if(toolboxMenuState == OBJECTS && mousePositionY > 150 && mousePositionX)
		{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();
			changingObjectInMap(mousePos);
		}
		else if(toolboxMenuState == GROUNDS && mousePositionY > 150 && mousePositionX)
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

	if(event.Type == sf::Event::KeyPressed)
	{
		if(event.Key.Code == sf::Key::LControl && lControlPressed == false)
		{
			lControlPressed = true;
		}

		if(event.Key.Code == sf::Key::LShift && lShiftPressed == false)
		{
			lShiftPressed = true;
		}

		if(lControlPressed == true)
		{

			if((event.Key.Code >= sf::Key::Num0) && (event.Key.Code <= sf::Key::Num9))
				{
					if(chosenTileFromToolbox > 0)
					{	
						hotKeys[event.Key.Code - 48] = chosenTileFromToolbox;
					}
				}

			if(event.Key.Code == sf::Key::L)
			{
				LoadMap("Data/Maps/Test.map");
			}
		}

		if(lControlPressed == false)
		{
			if((event.Key.Code >= sf::Key::Num0) && (event.Key.Code <= sf::Key::Num9))
				{
					if(hotKeys[event.Key.Code - 48] > 0)
					{	
						toolboxFirstFieldNumber = hotKeys[event.Key.Code - 48];
					}
				}
		}
		

		if(event.Key.Code == sf::Key::D)
		{
			if(toolboxFirstFieldNumber > 1)
				toolboxFirstFieldNumber --;
		}

		if(event.Key.Code == sf::Key::A)
		{
			if(toolboxFirstFieldNumber < tileSprites.size())
			toolboxFirstFieldNumber ++;
		}

	}

	
	if((event.Type == sf::Event::KeyReleased) && (event.Key.Code == sf::Key::LControl))
	{
		lControlPressed = false;
	}

	if((event.Type == sf::Event::KeyReleased) && (event.Key.Code == sf::Key::LShift))
	{
		lShiftPressed = false;
	}


	if((event.Type == sf::Event::MouseButtonPressed) && (event.Key.Code == sf::Mouse::Left))
	{
			sf::Vector2i mousePos;
			mousePos.x = steering.GetMouseX();
			mousePos.y = steering.GetMouseY();

		if(mousePos.y < 120)
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

	noOfTilesVisible.x = (int)(SCREEN_WIDTH/32);
	noOfTilesVisible.y = (int)(SCREEN_WIDTH/32);

	int numberOfToolboxRectangles = (int)((SCREEN_WIDTH-20)/96) - 1;

	for(int rectangleCreator = 1; rectangleCreator <= numberOfToolboxRectangles ; rectangleCreator ++)
	{
		toolboxRectangles[rectangleCreator] = sf::IntRect (20 + (rectangleCreator - 1)*96 , 20, 84 + (rectangleCreator - 1)*96 , 84);
	}

}

void MapCreator::toolboxManagement(sf::Vector2i toolboxClickPosition)
{
	if(toolboxMenuState == SUBMENU_CHOICE)
	{
		if(submenuButtonRectangles[0].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			toolboxMenuState = GROUNDS;
		}
		else if(submenuButtonRectangles[1].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			toolboxMenuState = OBJECTS;
		}
		else if(submenuButtonRectangles[2].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			toolboxMenuState = ENEMIES;
		}
		else if(submenuButtonRectangles[3].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			saveMap("Test");
		}
	}

	else if (toolboxMenuState == GROUNDS)
	{
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
	}

	else if (toolboxMenuState == OBJECTS)
	{
		for(unsigned int rectangleCheckIterator = 1; rectangleCheckIterator <= toolboxRectangles.size(); rectangleCheckIterator++)
		{
			if(toolboxRectangles[rectangleCheckIterator].Contains(toolboxClickPosition.x, toolboxClickPosition.y))
			{
				unsigned int tempCheck = rectangleCheckIterator + (toolboxFirstFieldNumber - 1);
				if(tempCheck >= 1 && tempCheck < objectSprites.size())
				{
					chosenObjectFromToolbox = tempCheck;
				}
			}
		}
	}

	if(toolboxMenuState != SUBMENU_CHOICE)
	{
		if(submenuReturnButtonRectangle.Contains(toolboxClickPosition.x, toolboxClickPosition.y))
		{
			toolboxMenuState = SUBMENU_CHOICE;
		}
	}

}


void MapCreator::changingSpriteInMap(sf::Vector2i mapClickPosition)
{
	sf::Vector2i realClickPosition;
	realClickPosition.x = (int)(cameraPosition.x - 370 + mapClickPosition.x);
	realClickPosition.y = (int)(cameraPosition.y - 350 + mapClickPosition.y);
	if(realClickPosition.x > 0 && realClickPosition.y > 0 && (unsigned int)(realClickPosition.x/32) < Size && (unsigned int)(realClickPosition.y/32) <Size)
	{
		if(!lShiftPressed && chosenTileFromToolbox != 0)
		{
			createdMap[realClickPosition.y/32][realClickPosition.x/32].changeType(chosenTileFromToolbox);
		}
		else if(lShiftPressed)
		{
			createdMap[realClickPosition.y/32][realClickPosition.x/32].changeType(1);
		}
	}

}

void MapCreator::changingObjectInMap(sf::Vector2i mapClickPosition)
{
	sf::Vector2i realClickPosition;
	realClickPosition.x = (int)(cameraPosition.x - 370 + mapClickPosition.x);
	realClickPosition.y = (int)(cameraPosition.y - 350 + mapClickPosition.y);
	if(realClickPosition.x > 0 && realClickPosition.y > 0 && (unsigned int)(realClickPosition.x/16) < Size*2 && (unsigned int)(realClickPosition.y/16) <Size*2)
	{
		if(!lShiftPressed && chosenObjectFromToolbox >0)
		{
			mapObjects[realClickPosition.y/16][realClickPosition.x/16].changeType(chosenObjectFromToolbox);
		}
		else if(lShiftPressed)
		{
			mapObjects[realClickPosition.y/16][realClickPosition.x/16].changeType(0);
		}
	}

}
 

MapCreator::~MapCreator()
{
	
	if(createdMap != NULL)
	{
	for(unsigned int i = 0; i < Size; ++i)
    delete [] createdMap[i];
	delete [] createdMap;


	for(unsigned int i = 0; i < 2*Size; ++i)
    delete mapObjects[i];
	delete mapObjects;

	for(int i = 0; i < 6; i++)
	{
		delete submenuButtonSprite[i];
	}

	}

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
						
							if(str[0] == '-')
						{
							break;
						}

							if(str.size() != 1)
								outputFile << str << " " ;
							else
							{
								outputFile << str << " ";
								dataSet >> str;
								outputFile << str << "\n";
							}

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

bool MapCreator::LoadMap(const std::string& filename)
{
	std::ifstream map(filename.c_str());
		 if (!map) 
		 {
			std::cerr << "Nie udalo sie zaladowac pliku mapy!!! " << filename << "\n";
			return false;
		 }

		   std::string stringRepresentingFileLine;
		  std::string mapTilesPath;
		  bool looping = true;

		   for(unsigned int i = 0; i < Size; ++i)
			delete [] createdMap[i];
			delete [] createdMap;

			for(unsigned int i = 0; i < 2*Size; ++i)
			delete mapObjects[i];
			delete mapObjects;

		  do{
			 if(map.good())
				 {
					 getline (map,stringRepresentingFileLine);
					 if(stringRepresentingFileLine.at(0) != '*')
						{
						std::istringstream iss(stringRepresentingFileLine);
						iss >> Size;
						}
					 else
					 {
						 looping = false;
					 }
				 }
		  }while(looping);

		
		createdMap = new Tile*[Size];
		for(unsigned int i = 0; i < Size; ++i)
			createdMap[i] = new Tile[Size];


		mapObjects = new MapObject*[Size*2];
		for(unsigned int i = 0; i < Size*2; ++i)
		mapObjects[i] = new MapObject[Size*2];



		looping = true;		

			 //getting paths from the beggining of file
			 do{
				 if(map.good())
				 {
					 getline (map,stringRepresentingFileLine);
					 if(stringRepresentingFileLine.at(0) != '*')
						{
						std::istringstream iss(stringRepresentingFileLine);
						iss >> mapTilesPath;
						}
					 else
					 {
						 mapTilesPath = "Data/Textures/MapTiles/";
						 looping = false;
					 }
				 }
			 }while(looping);

			 //---------------

			 looping = true;
			 std::string substring;

			 //passing info about map tiles' graphics (first row of map file)
			 do{
				if(map.good())
				{
					getline (map,stringRepresentingFileLine);

					if(stringRepresentingFileLine.at(0) != '*')
					{

					}
					else
					{
						looping = false;
					}
				}
			 }while(looping);

			 //------------

			 looping = true;

			  do{
				if(map.good())
				{
					getline (map,stringRepresentingFileLine);

					if(stringRepresentingFileLine.at(0) != '*')
					{

					}
					else
					{
						looping = false;
					}
				}
				else
				{
					std::cout<<"map is not good\n";
					break;

				}
			 }while(looping);


			  //------------------------
			  	int rowNumber = 0;
				int colNumber = 0;


			  while ( map.good() )
				{
						int fieldType = -1;
						 getline (map,stringRepresentingFileLine);
					
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub;

				 looping = true;
				 int tileType = -1;
						do
						{
						iss >>sub;
						if(sub.at(0) == '*')
						{
							break;
						}
						//geting type of tile <ID 1,2,3... which tells what is it's picture
							tileType = atoi(sub.c_str());
							createdMap[rowNumber][colNumber] = Tile(tileType,colNumber*32 - 32, 48 + rowNumber*32);
							colNumber++;
							if(colNumber == Size)
							{
								break;
							}

						}
						while(iss);

						rowNumber++;					

						colNumber = 0;

						if(sub.at(0) == '*')
							{
								break;
							}

				}

			
			  //---------------------------

			  rowNumber = 0;

			  while ( map.good() )
				{
				colNumber = 0;
				 getline (map,stringRepresentingFileLine);
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub;
				 looping = true;
						do
						{
							if((unsigned int)colNumber >= 2*Size)
							{
								break;
							}

						iss >>sub;
						if(sub.at(0) == '*')
						{
							break;
						}
						mapObjects[rowNumber][colNumber] = MapObject (atoi(sub.c_str()), colNumber * 16 - 32,48 + rowNumber * 16);
						
						colNumber++;
						}
						while(iss);

						rowNumber++;
						if(rowNumber == 2*Size)
						{
							break;
						}

				}

			  std::cout << "Editor says: Map loaded succesfully!" << std::endl;
			  map.close();

	return true;
}