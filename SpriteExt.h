/*
 * Rozszerzona klasa sf::Sprite, która dodaje obsługę kolizji.
 */

#ifndef SPRITEEXT_H
#define SPRITEEXT_H

#include <SFML/Graphics.hpp>
#include "Collision/BoxMask.h"
#include "Collision/CircleMask.h"

class SpriteExt : public sf::Sprite
{
private:
	CollisionMask* collision_mask;
public:
	SpriteExt();
	~SpriteExt();
	void setBoxMask(const sf::IntRect&);
	void setCircleMask( int, int, int );
	CollisionMask* getCollisionMask();
};

#endif
