#include "MapObject.h"

MapObject::MapObject(int _objectType, sf::Vector2i _objectPosition)
{
	objectType = _objectType;
	objectPosition = _objectPosition;
}

MapObject::MapObject(int _objectType, int posX, int posY)
{
	objectType = _objectType;
	objectPosition.x = posX;
	objectPosition.y = posY;
}

MapObject::MapObject()
{
	objectType = -1;
	sf::Vector2i defaultPosition(0,0);
	objectPosition = defaultPosition;
}

void MapObject::changeType(int _type)
{
	objectType = _type;
}

sf::Vector2i MapObject::getPosition()
{
	return objectPosition;
}

int MapObject::getType()
{
	return objectType;
}