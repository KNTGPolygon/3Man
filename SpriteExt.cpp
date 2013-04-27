#include <stdlib.h>
#include "SpriteExt.h"

SpriteExt::SpriteExt()
{
	collision_mask = NULL;
	type = "";
}

void SpriteExt::setBoxMask(const sf::IntRect& _rect)
{
	collision_mask = new BoxMask(_rect);
	collision_mask->setType(BOX);
}

void SpriteExt::setCircleMask(int _x, int _y, int _radius)
{
	collision_mask = new CircleMask( _x, _y, _radius );
	collision_mask->setType(CIRCLE);
}


CollisionMask* SpriteExt::getCollisionMask()
{
	return collision_mask;
}

void SpriteExt::setType(std::string str)
{
	type = str;
}

std::string SpriteExt::getType()
{
	return type;
}

SpriteExt::~SpriteExt()
{
	if ( collision_mask != NULL )
		delete collision_mask;
}
