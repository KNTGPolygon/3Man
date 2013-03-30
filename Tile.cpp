#include "Tile.h"

Tile::Tile(int _type, int pos_x, int pos_y)
{
	type = _type;
	drawingPosition.x = pos_x;
	drawingPosition.y = pos_y;

}

Tile::Tile()
{
	type = -1;
}


int Tile::getType()
{
	return type;
}

sf::Vector2i Tile::getPosition()
{
	return drawingPosition;
}

	void Tile::changeType(int type)
	{
		this->type = type;
	}