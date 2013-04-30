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
	int Size;
	std::vector<std::string> addresses;
	Tile ** map_data;

	std::map <int, sf::Image> mapGraphics;
	std::map <int, sf::Sprite> tileSprites;
	


public:
	Maps(const std::string& filename);
	~Maps();
	void showMap(sf::RenderWindow *window, sf::Vector2f heroPosition);
	void getTileGraphicsAddressesSet(std::string str, std::string path);
	void createTiles();


};

#endif


//30 30		//map size in format rows x columns number
//*
