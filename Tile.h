#pragma once

#include <SFML/Graphics.hpp>

#ifndef TILE_H
#define TILE_H

class Tile{
public:
	int type;
	sf::Sprite fieldSprite;				
	sf::Image MyTexture;

public:
	Tile(int _type);
	Tile();
	void loadSetOfGraphics(const std::string& filename);

};

#endif