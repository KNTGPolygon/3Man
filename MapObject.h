#pragma once

#include <SFML/Graphics.hpp>

#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

class MapObject
{
private:
	sf::Vector2i objectPosition;
	int objectType;

public:

	MapObject(int _objectType, sf::Vector2i _objectPosition);

};

#endif