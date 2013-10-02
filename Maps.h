#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "Tile.h"
#include "MapObject.h"
#include "GameObject.h"

#ifndef MAPS_H
#define MAPS_H

#include <sstream>

class Maps{

private:
	int clockCounter;

	int Size;
	int numberOfObjects;
	std::map<const int, std::string> addresses;
	Tile ** map_data;
	GameObject ** mapGameObjects;
	std::map <int, int> typeOfTileAnimations;

	std::map <int, sf::Image> mapGraphics;
	std::map <int, sf::Sprite> tileSprites;


	


public:
	Maps(const std::string& filename);
	~Maps();
	void showMap(sf::RenderWindow *window, sf::Vector2f heroPosition);
	int getSize();
	int getNoOfObjects();
	GameObject ** getMapGameObjects();

private:
	void animate();
	void createTiles();
};

#endif
