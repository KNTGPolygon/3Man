#pragma once

#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include <iostream>

#ifndef TILE_H
#define TILE_H

class Tile{
public:
	int type;
	//sf::Sprite tileSprite;				
	sf::Image tileTexture;
	sf::Vector2i drawingPosition;

public:
	Tile(int _type, int pos_x = 0, int pos_y = 0);
	Tile(int _type, const std::string& filename);
	Tile();
	void loadSetOfGraphics(const std::string& filename);
	int getType();
	sf::Vector2i getPosition();

};

#endif