#include "Maps.h"
#include <fstream>

Maps::Maps(const std::string& filename)
{
	int Size = 30;

	//creating dynamic two-dimensional array (tiles created with default constructor, each with type = -1)
	map_data = new Tile*[Size];
	for(int i = 0; i < Size; ++i)
    map_data[i] = new Tile[Size];

	int storedColNumber = 0;
	rowNumber = 0;
	colNumber = 0;
	map_data[0][0] = 0;

	//checking whether file can be opened
	std::ifstream map(filename.c_str());
		 if (!map) {
        std::cerr << "Nie uda�o si� za�adowa� pliku " << filename << "\n";
				 }
		 else
		 {
			 std::string stringRepresentingFileLine;

			 bool loopingOrFirst = true;
			 //passing info about map tiles' graphics (first row of map file)
			 do{
				if(map.good())
				{
					getline (map,stringRepresentingFileLine);
					if(stringRepresentingFileLine.at(0) == '.')
					{
					getTileGraphicsAddressesSet(stringRepresentingFileLine);
					}
					else
					{
						loopingOrFirst = false;
					}
				}
			 }while(loopingOrFirst);

			 loopingOrFirst = true;

				//decoding map (from second row)
			  while ( map.good() )
				{

					if(loopingOrFirst == false)
					{
						 getline (map,stringRepresentingFileLine);
					}
					else
					{
						loopingOrFirst = false;
					}
				 std::istringstream iss(stringRepresentingFileLine);
				 std::string sub;
						do
						{
						iss >>sub;
							
							map_data[rowNumber][colNumber] = Tile(atoi(sub.c_str()), 0 + colNumber * 64, 0+rowNumber*64);
							colNumber++;
							storedColNumber = colNumber-1;
						}
						while(iss);

						rowNumber++;
						colNumber = 0;

				}
			  colNumber = storedColNumber;
				
		 }
		 map.close();

		 createTiles();

}
void Maps::showMap(sf::RenderWindow *window)
{	
	for(int row = 0; (unsigned)row < rowNumber; row ++)
	{

		for(int col = 0; col < colNumber; col ++)
		{
			sf::Vector2i tilePosition = map_data[row][col].getPosition();
			tileSprites[map_data[row][col].getType()].SetPosition(tilePosition.x,tilePosition.y);
			window->Draw(tileSprites[map_data[row][col].getType()]);
		}
	}
}

void Maps::getTileGraphicsAddressesSet(std::string str)
{
	 std::istringstream iss(str);
	 int place = 0;
	 std::string path = "Data/Textures/MapTiles/";
	 std::string sub;


				do
				{	
					place = 0;
					iss >> sub;

					if(sub.at(0) != '.')
					{
					place = atoi(sub.substr(0,sub.find_first_of("-")).c_str());
					}

					if(place > addresses.size() && place > 0 )
					{
						addresses.resize(place);
					}

					sub = sub.substr(sub.find_first_of("-") + 1, sub.size());

					if(!sub.empty() && sub.size() != 0 && place != 0)
					{
					addresses.insert(addresses.begin() + place, (path + sub + ".png").c_str()) ;
					}
				} while (iss);

				
}

void Maps::createTiles()
{
	
	//i<addresses.size() cause last field is empty, we have to make it safe somehow
	for(int i = 1; i < addresses.size(); i++)
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
	for ( int i = 0; i < 30; i++ )
		delete map_data[i];

	delete[] map_data;
}
