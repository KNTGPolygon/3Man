#include "Maps.h"
#include <fstream>

Maps::Maps(const std::string& filename)
{


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

			 //passing info about map tiles' graphics (first row of map file)
			 do{
				if(map.good())
				{
					getline (map,stringRepresentingFileLine);
					if(stringRepresentingFileLine.at(0) != '*')
					{
					getTileGraphicsAddressesSet(stringRepresentingFileLine, mapTilesPath);
					}
					else
					{
						looping = false;
					}
				}
			 }while(looping);


			  while ( map.good() )
				{
						int fieldType = -1;
						 getline (map,stringRepresentingFileLine);
					
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub;

				 looping = true;
						do
						{
						iss >>sub;
						if(sub.at(0) == '*')
						{
							break;
						}
						
							map_data[rowNumber][colNumber] = Tile(atoi(sub.c_str()), 0 + colNumber * 64, 0+rowNumber*64);
							colNumber++;
						}
						while(iss);

						rowNumber++;
						colNumber = 0;

						if(sub.at(0) == '*')
							{
								break;
							}

				}
				
		 map.close();

		 createTiles();


}
void Maps::showMap(sf::RenderWindow *window, sf::Vector2f heroPosition)
{	

	sf::Vector2i leftTopFieldVisible;
	sf::Vector2i rightBotFieldVisible;

	// these numbers are from tests : subtraction because of "how many fields hero can see to the left and top" and addition "how many to the right and bot + what we subtracted"
	leftTopFieldVisible.x = (int)(heroPosition.x / 64) - 7;
	leftTopFieldVisible.y = (int)(heroPosition.y / 64) - 7;
	rightBotFieldVisible.x = leftTopFieldVisible.x + 15;
	rightBotFieldVisible.y = leftTopFieldVisible.y + 13;

	leftTopFieldVisible.x = (leftTopFieldVisible.x >= 0)? leftTopFieldVisible.x : 0;
	leftTopFieldVisible.y = (leftTopFieldVisible.y >= 0)? leftTopFieldVisible.y : 0;
	rightBotFieldVisible.x = (rightBotFieldVisible.x <= Size)? rightBotFieldVisible.x : Size;
	rightBotFieldVisible.y = (rightBotFieldVisible.y <= Size)? rightBotFieldVisible.y : Size;

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

void Maps::getTileGraphicsAddressesSet(std::string str, std::string path)
{
	//str is representation of line (eg. 01-grass) that we got from main loop
	 std::istringstream iss(str);
	 unsigned int place = 0;
	 std::string sub;

		place = 0;
		iss >> sub;
			
		//getting tile type number
		place = atoi(sub.substr(0,sub.find_first_of("-")).c_str());

		//resizing addresses vector (so that system will handle it more easily)
		if(place > addresses.size() && place > 0 )
		{
			addresses.resize(place);
		}

		//getting tile filename
		sub = sub.substr(sub.find_first_of("-") + 1, sub.size());
		
		addresses.insert(addresses.begin() + place, (path + sub).c_str()) ;
}

void Maps::createTiles()
{
	
	//i<addresses.size() cause last field is empty, we have to make it safe somehow
	for(unsigned int i = 1; i < addresses.size(); i++)
	{
		
		mapGraphics[i].LoadFromFile(addresses.at(i));
	}

	sf::Sprite tempSprite;
	for(unsigned int i = 1; i <= mapGraphics.size(); i++)
	{
		mapGraphics[i].SetSmooth(false);
		tempSprite.SetImage(mapGraphics[i]);
		tileSprites[i] = tempSprite;
		
	}
}

Maps::~Maps()
{
	delete[] map_data;
}
