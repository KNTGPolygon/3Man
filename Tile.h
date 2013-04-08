#pragma once

#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include <iostream>

#ifndef TILE_H
#define TILE_H

class Tile{
public:
	int type;			
	sf::Vector2i drawingPosition;

public:
	Tile(int _type, int pos_x = 0, int pos_y = 0);
	Tile();
	int getType();
	sf::Vector2i getPosition();
	void changeType(int type);

	~Tile();

};

#endif