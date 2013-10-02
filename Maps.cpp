#include "Maps.h"
#include "GameEngine.h"
#include <fstream>
#include <vector>

Maps::Maps(const std::string& filename)
{
	clockCounter = 1;

	MapObject **tempConstructorObjects;
	std::map <const int, std::string> tempAddressesArray;

	std::map <int, int> passageRightsRead;

	//checking whether file can be opened
	std::ifstream map(filename.c_str());
		 if (!map) 
		 {
			std::cerr << "Nie udalo sie zaladowac pliku mapy!!! " << filename << "\n";
			return;
		 }

		  std::string stringRepresentingFileLine;
		  std::string mapTilesPath;
		  bool looping = true;

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

	//creating dynamic two-dimensional array (tiles created with default constructor, each with type = -1)
	map_data = new Tile*[Size];
	for(int i = 0; i < Size; ++i)
    map_data[i] = new Tile[Size];

	//creating temporary array for map objects (for storing loaded data)
	tempConstructorObjects = new MapObject*[Size*2];
	for(int i = 0; i < Size*2; ++i)
    tempConstructorObjects[i] = new MapObject[Size*2];


	int rowNumber = 0;
	int colNumber = 0;

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

			looping = true;
			 unsigned int counter = 1;
			 std::string substring;

			 //passing info about map tiles' graphics (first row of map file)
			 do{
				if(map.good())
				{
					getline (map,stringRepresentingFileLine);
					std::istringstream iss(stringRepresentingFileLine);

					if(stringRepresentingFileLine.at(0) != '*')
					{
						//std::cout << mapTilesPath << " " <<  stringRepresentingFileLine << std::endl;
						iss >> substring;
						addresses[counter] = (mapTilesPath + substring).c_str() ;

						iss >> substring;
						passageRightsRead[counter] =atoi(substring.c_str());

						iss >> substring;
						typeOfTileAnimations[counter] =atoi(substring.c_str());

						counter++;
					}
					else
					{
						looping = false;
					}
				}
			 }while(looping);

//-------------------------
			 looping = true;
			
			 std::string objectPath = "Data/Textures/MapObjects/";
			 counter = 1;
			 do{
				if(map.good())
				{
					getline (map,stringRepresentingFileLine);
					std::istringstream iss(stringRepresentingFileLine);

					if(stringRepresentingFileLine.at(0) != '*')
					{
						iss >> substring;
						tempAddressesArray[counter] = (objectPath + substring).c_str();
						counter++;
					}
					else
					{
						looping = false;
						counter = 0;
					}
				}
				else
				{
					std::cout<<"map is not good\n";
					break;

				}
			 }while(looping);


//------------------------
			  while ( map.good() )
				{
						int fieldType = -1;
						 getline (map,stringRepresentingFileLine);
					
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub;

				 looping = true;
				 int tileType;
						do
						{
						iss >>sub;
						if(sub.at(0) == '*')
						{
							break;
						}
						//geting type of tile <ID 1,2,3... which tells what is it's picture
							tileType = atoi(sub.c_str());
							map_data[rowNumber][colNumber] = Tile(tileType, 0 + colNumber * 64, 0+rowNumber*64, passageRightsRead[tileType]);
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
						tempConstructorObjects[rowNumber][colNumber] = MapObject (atoi(sub.c_str()), colNumber * 32, rowNumber * 32);
						
						colNumber++;
						}
						while(iss);

						rowNumber++;

						if(rowNumber == 2*Size)
						{
							break;
						}

				}

			   std::map<const int, GameObject*> reducedTempConstructorObjects;
			   counter = 1;
			   sf::Vector2i position;
			   std::vector< sf::Vector3i > objects;
			   sf::Vector3i tempVector;
			   
			   for(unsigned int i = 0; i < 2*Size ; i++)
			   {
				   for(unsigned int j = 0; j < 2 * Size; j++)
				   {
					   if(tempConstructorObjects[i][j].getType() > 0)
					   {
						 tempVector.x = i;
						 tempVector.y = j;
						 tempVector.z = tempConstructorObjects[i][j].getType();
						 objects.push_back( tempVector );
						   position = tempConstructorObjects[i][j].getPosition();
						   unsigned int addressNumber = tempConstructorObjects[i][j].getType();
						  reducedTempConstructorObjects[counter] = new GameObject((float)position.x, (float)position.y, addressNumber,tempAddressesArray[addressNumber]);
						  counter++;
					   }

					   
				   }
			   }
			   GameEngine::getInstance()->SetMapObjectsGrid( objects, 2*Size );
			   std::cout << " Created tempConstructorObjects! " << std::endl;

			    for(unsigned int i = 0; i < 2*Size ; i++)
			   {
					delete [] tempConstructorObjects[i];
			   }
				delete [] tempConstructorObjects;

				numberOfObjects = reducedTempConstructorObjects.size();
				mapGameObjects = new GameObject*[reducedTempConstructorObjects.size()];

				sf::Vector2f pos;
				for(unsigned int i = 0; i < reducedTempConstructorObjects.size(); i++)
				{
					pos = reducedTempConstructorObjects[i+1]->GetPosition();
					int type = reducedTempConstructorObjects[i+1]->getType();
					mapGameObjects[i] = new GameObject(pos.x, pos.y, type, tempAddressesArray[type]);//reducedTempConstructorObjects[i+1];
				}

				for(unsigned int i = 0; i < reducedTempConstructorObjects.size(); i++)
				{
					delete reducedTempConstructorObjects[i+1];
				}
				
				std::cout << " Map loaded succesfully! " << std::endl;

		 map.close();

		 createTiles();

		 //----------------------
}
void Maps::showMap(sf::RenderWindow *window, sf::Vector2f heroPosition)
{		
	animate();

	sf::Vector2i leftTopFieldVisible;
	sf::Vector2i rightBotFieldVisible;

	// these numbers are from tests : subtraction because of "how many fields hero can see to the left and top" and addition "how many to the right and bot + what we subtracted"
	leftTopFieldVisible.x = (int)(heroPosition.x / 64) - 7;
	leftTopFieldVisible.y = (int)(heroPosition.y / 64) - 7;
	rightBotFieldVisible.x = leftTopFieldVisible.x + 15;
	rightBotFieldVisible.y = leftTopFieldVisible.y + 13;

	leftTopFieldVisible.x = (leftTopFieldVisible.x >= 0)? leftTopFieldVisible.x : 0;
	leftTopFieldVisible.y = (leftTopFieldVisible.y >= 0)? leftTopFieldVisible.y : 0;
	rightBotFieldVisible.x = (rightBotFieldVisible.x <= (int)Size)? rightBotFieldVisible.x : Size;
	rightBotFieldVisible.y = (rightBotFieldVisible.y <= (int)Size)? rightBotFieldVisible.y : Size;

	for(unsigned int row = (unsigned int)leftTopFieldVisible.y; row < (unsigned int)rightBotFieldVisible.y; row ++)
	{
		for(unsigned int col = (unsigned int)leftTopFieldVisible.x; col < (unsigned int)rightBotFieldVisible.x; col ++)
		{
			sf::Vector2i tilePosition = map_data[row][col].getPosition();
			tileSprites[map_data[row][col].getType()].SetPosition((float)tilePosition.x,(float)tilePosition.y);
			window->Draw(tileSprites[map_data[row][col].getType()]);
		}
	}

}

void Maps::animate()
{
	
	int period = 300;

	if(clockCounter == 1)
	{
		for(unsigned int i = 1; i <= mapGraphics.size(); i++)
		{
			if(typeOfTileAnimations[i]==1)
			tileSprites[i].SetColor(sf::Color(255,255,255,255));
		}
	}
	
	if(clockCounter > 0 && clockCounter <= period)
	{
		int change = clockCounter / 5;
		for(unsigned int i = 1; i <= mapGraphics.size(); i++)
		{
			if(typeOfTileAnimations[i]==1)
			tileSprites[i].SetColor(sf::Color(255,255,255,255 - change));
		}
	}

	if(clockCounter > period && clockCounter < 2*period)
	{
		int change = (2*period - clockCounter)/ 5;
		for(unsigned int i = 1; i <= mapGraphics.size(); i++)
		{
			if(typeOfTileAnimations[i]==1)
			tileSprites[i].SetColor(sf::Color(255,255,255,255 - change));
		}
	}

	if(clockCounter == 2*period)
	{
		clockCounter = 0;
	}

	clockCounter++;
}

void Maps::createTiles()
{
	
	//i<addresses.size() cause last field is empty, we have to make it safe somehow
	for(unsigned int i = 1; i <= addresses.size(); i++)
	{
		mapGraphics[i].LoadFromFile(addresses[i]);
		mapGraphics[i].CreateMaskFromColor(sf::Color(255,0,255));
	}

	sf::Sprite tempSprite;
	for(unsigned int i = 1; i <= mapGraphics.size(); i++)
	{
		mapGraphics[i].SetSmooth(false);
		tempSprite.SetImage(mapGraphics[i]);
		tileSprites[i].SetColor(sf::Color(255,255,255,240));
		tileSprites[i] = tempSprite;
		
	}

		std::cout << " Map tiles created in map.cpp " << std::endl;

}

Maps::~Maps()
{
	for(unsigned int i = 0; i < Size; i++)
	{
		delete []map_data [i];
	}
	delete[] map_data;

	for(int i = 0; i < numberOfObjects; i++)
	{
		delete mapGameObjects[i];
	}
}

int Maps::getSize()
{
	if(Size <= 0)
	{
		std::cout << "Something is wrong with map size!!! " << std::endl;
	}
	return Size;
}

int Maps::getNoOfObjects()
{
	std::cout << "Number of objects: " << numberOfObjects << std::endl;
	return numberOfObjects;
}

GameObject ** Maps::getMapGameObjects()
{
	return mapGameObjects;
}
