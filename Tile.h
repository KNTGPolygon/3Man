#pragma once

#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include <iostream>

#ifndef TILE_H
#define TILE_H

enum passageRights {FREE, NO_PASSAGE, DANGEROUS_LOW_DAMAGE,  DANGEROUS_MEDIUM_DAMAGE,  DANGEROUS_HIGH_DAMAGE};

class Tile{

private:
	int type;			
	sf::Vector2i drawingPosition;
	passageRights rights;
	int damage;

public:
	Tile(int _type, int pos_x = 0, int pos_y = 0, int right = (passageRights)0);
	Tile();
	int getType();
	sf::Vector2i getPosition();
	void changeType(int type);
	int getPassageRights();
	int getDamage();

	~Tile();

};

#endif