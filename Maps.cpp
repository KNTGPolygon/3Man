#include "Maps.h"
#include "GameEngine.h"
#include <fstream>
#include <vector>

Maps::Maps(const std::string& filename)
{

	clockCounter = 1;
	numberOfObjects = 0;

	MapFileLoading(filename);

	CreateTiles();

}

void Maps::MapFileLoading(const std::string& filename)
{
	std::map <const int, std::string> tempAddressesArray;
	std::map <int, int> passageRightsRead;

	//checking whether file can be opened
	std::ifstream map(filename.c_str());
		 if (!map) 
		 {
			std::cerr << "Nie udalo sie stworzyæ strumienia wejœcia do programu z pliku mapy!!! " << filename << "\n";
			return;
		 }

	std::string stringRepresentingFileLine;

	MapFileLoading_GetMapSize(map);
	MapFileLoading_PrepareTileArrayAccordingToSize();

	int rowNumber = 0;
	int colNumber = 0;

	 bool looping = true;	
	std::string mapTilesPath = "Data/Textures/MapTiles/";
			 

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
			
			 int numberOfNonActiveObjects = 0;
			 std::string objectPath = "Data/Textures/MapObjects/";
			 counter = 0;
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
						numberOfNonActiveObjects++;
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

			   std::vector <sf::Vector3i> temp_ObjectVectorRepresentations;
			   int objectType = 0;

			   std::vector< sf::Vector3i > objects;
			   sf::Vector3i tempVector;

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

						objectType = atoi(sub.c_str());

						if(objectType > 0)
						{
							tempVector.x = rowNumber;
							tempVector.y = colNumber;
							tempVector.z = objectType;
							objects.push_back( tempVector );

							temp_ObjectVectorRepresentations.push_back(sf::Vector3i(colNumber * 32, rowNumber * 32, objectType));
							arrayOfFieldsOccupiedWithObjects[rowNumber][colNumber] = 1;
						}
						else
						{
							arrayOfFieldsOccupiedWithObjects[rowNumber][colNumber] = -1;
						}
						
						
						colNumber++;
						}
						while(iss);

						rowNumber++;

						if(rowNumber >= 2*Size)
						{
							break;
						}

				}

			   numberOfObjects = temp_ObjectVectorRepresentations.size();

			   sf::Vector2i objectPosition;

			   std::vector < sf::Vector3i >activeElementsVector;
				for(unsigned int i = 0; i < numberOfObjects; i++)
				{
					objectPosition = sf::Vector2i(temp_ObjectVectorRepresentations.at(i).x, temp_ObjectVectorRepresentations.at(i).y);
					objectType = temp_ObjectVectorRepresentations.at(i).z;

					if(objectType < numberOfNonActiveObjects)
						mapGameObjects.push_back(new GameNonActiveObject(objectPosition.x, objectPosition.y, objectType, tempAddressesArray[objectType]));
					else
						activeElementsVector.push_back(sf::Vector3i(objectPosition.x, objectPosition.y, objectType));
				}


			   int objectArraySize = 2*Size;
			   
			   GameEngine::getInstance()->SetMapObjectsGrid( objects, 2*Size );

			    MapFileLoading_SkipFileLine(map);
				MapFileLoading_GetEnemies(map);



				counter = 0;

				
				while ( map.good() )
				{
				 getline (map,stringRepresentingFileLine);
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub; 

				 looping = true;
				 iss >>sub;

				 if(sub.at(0) == '*')
						{
							break;
						}

						std::cout << sub << std::endl;
						addressesOfActiveGraphics[counter] = sub;
						counter++;
				}

				for(int x = 0; x < 3 ; x++)
				{
					std::cout << addressesOfActiveGraphics[x] << std::endl;
				}
				
				for(int i = 0; i < activeElementsVector.size(); i++)
				{
					sf::Vector3i tempVector = activeElementsVector.at(i);
					mapGameActiveObjects.push_back(new GameActiveObject(tempVector.x, tempVector.y, tempVector.z, addressesOfActiveGraphics[tempVector.z - numberOfNonActiveObjects]));
				}

				std::cout << " Map loaded succesfully! " << std::endl;


		 map.close();
}

void Maps::MapFileLoading_GetMapSize(std::ifstream& inputMapFileStream)
{
	std::string stringRepresentingFileLine = "";

	if(inputMapFileStream.good())
				 {
					getline (inputMapFileStream,stringRepresentingFileLine);
					std::istringstream iss(stringRepresentingFileLine);
					iss >> Size;
				 }

		 getline (inputMapFileStream,stringRepresentingFileLine);
}

void Maps::MapFileLoading_PrepareTileArrayAccordingToSize()
{
	map_data = new Tile*[Size];
	for(int i = 0; i < Size; ++i)
		map_data[i] = new Tile[Size];

	arrayOfFieldsOccupiedWithObjects = new int* [2*Size];
	for(int i = 0; i < 2*Size; ++i)
		arrayOfFieldsOccupiedWithObjects[i] = new int[2*Size];

}

void Maps::MapFileLoading_GetEnemies(std::ifstream& inputMapFileStream)
{
		int colNumber = 0;
		int rowNumber = 0;

		int enemyType = -1;

		std::string stringRepresentingFileLine = "";

		bool looping = true;

			  while ( inputMapFileStream.good() )
				{

				 enemyType = -1;
				 getline (inputMapFileStream,stringRepresentingFileLine);
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub;

						do
						{
						iss >>sub;

						if(sub.at(0) == '*')
							{
								break;
							}

						enemyType = atoi(sub.c_str());

						if(enemyType != -1)
							{

								if( enemyType != 11 )
								{
									enemyType = -9 + rand()%19;
									if( enemyType == 0 ) enemyType = 1;
								}

								listOfEnemies.push_back(sf::Vector3i(colNumber * 64,rowNumber * 64,enemyType));
							}

						colNumber++;

						if(colNumber == Size)
							{
								break;
							}

						}while(iss);

						rowNumber++;					

						colNumber = 0;

						if(sub.at(0) == '*')
							{
								break;
							}
				}
}



void Maps::MapFileLoading_SkipFileLine(std::ifstream& inputMapFileStream)
{
	std::string lineToIgnore = "";
	std::getline (inputMapFileStream,lineToIgnore);
}



void Maps::showMap(sf::RenderWindow *window, sf::Vector2f heroPosition)
{		
	Animate();

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

void Maps::Animate()
{

	int period = 300;

	if(clockCounter == 1)
	{
		for(unsigned int i = 1; i <= mapGraphics.size(); i++)
		{
			if(typeOfTileAnimations[i] == 1)
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

void Maps::CreateTiles()
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

	for(unsigned int i = 0; i < 2*Size; i++)
	{
		delete []arrayOfFieldsOccupiedWithObjects [i];
	}
	delete[] arrayOfFieldsOccupiedWithObjects;

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

std::vector<GameNonActiveObject *> Maps::getMapGameObjects()
{
	return mapGameObjects;
}

std::vector<GameActiveObject *> Maps::getMapActiveGameObjects()
{
	return mapGameActiveObjects;
}

std::vector<sf::Vector3i> Maps::GetListOfEnemies()
{
	return listOfEnemies;
}