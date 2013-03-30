#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "Tile.h"

#ifndef MAPS_H
#define MAPS_H

#include <sstream>

class Maps{

private:
	int rowNumber;
	int colNumber;
	std::vector<std::string> addresses;
	std::map<int, std::map<int, Tile> > map_data;

	std::map <int, sf::Image> mapGraphics;
	std::map <int, sf::Sprite> tileSprites;
	


public:
	Maps(const std::string& filename);
	void showMap(sf::RenderWindow *window);
	void getTileGraphicsAddressesSet(std::string str);
	void createTiles();


};

#endif