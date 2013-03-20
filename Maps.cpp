#include "Maps.h"
#include <fstream>

Maps::Maps(const std::string& filename)
{
	std::ifstream map(filename.c_str());
		 if (!map) {

        std::cerr << "Nie uda³o siê za³adowaæ pliku " << filename << "\n";

				 }
		 else
		 {
			 std::vector <Tile> temp;

			 std::string str;

			 bool loopingOrFirst = true;
			 //passing info about map tiles' graphics (first row of map file)
			 do{
				if(map.good())
				{
					getline (map,str);
					if(str.at(0) == '.')
					{
					getTileGraphicsAddressesSet(str);
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
						 getline (map,str);
					}
					else
					{
						loopingOrFirst = false;
					}
				 std::istringstream iss(str);

				do
				{
					std::string sub;
					iss >> sub;
					if(!sub.empty())
					{
						temp.push_back(Tile (atoi(sub.c_str())));
					}
				} while (iss);

				m_data.push_back(temp);
				temp.clear();
				}

				
		 }
		 map.close();
}
void Maps::showMap()
{	
	for(int vectorNum = 0; (unsigned)vectorNum < m_data.size(); vectorNum ++)
	{

		for(int i = 0; i < m_data.at(vectorNum).size(); i ++)
		{
			std::cout << m_data.at(vectorNum).at(i).type;
		}
		std::cout << std::endl;
	}
}

void Maps::getTileGraphicsAddressesSet(std::string str)
{
	 std::istringstream iss(str);
	 int place = 0;
	 std::string path = "Data/Textures/";
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
					addresses.insert(addresses.begin() + place, (path + sub + ".bmp").c_str()) ;
					}
				} while (iss);

				for(int i = 0; i<addresses.size(); i++)
				{
					std::cout << i << " " << addresses.at(i) << std::endl;
				}
				
}