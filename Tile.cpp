#include "Tile.h"

Tile::Tile(int _type, int pos_x, int pos_y, int right)
{
	type = _type;
	drawingPosition.x = pos_x;
	drawingPosition.y = pos_y;
	rights = (passageRights)right;

	if(rights == DANGEROUS_LOW_DAMAGE)
	{
		damage = 5;
	}
	else if(rights == DANGEROUS_MEDIUM_DAMAGE)
	{
		damage = 10;
	}
	else if(rights == DANGEROUS_HIGH_DAMAGE)
	{
		damage = 20;
	}

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

	int Tile::getPassageRights()
	{
		return rights;
	}

	int Tile::getDamage()
	{
		return damage;
	}

	Tile::~Tile()
	{

	}