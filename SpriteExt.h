/*
 * Rozszerzona klasa sf::Sprite, która dodaje obsługę kolizji.
 */

#ifndef SPRITEEXT_H
#define SPRITEEXT_H

#include <SFML/Graphics.hpp>
#include "Collision/BoxMask.h"
#include "Collision/CircleMask.h"
#include <string>

class SpriteExt : public sf::Sprite
{
private:
	CollisionMask* collision_mask;
	std::string type;
public:
	SpriteExt();
	~SpriteExt();
	void setBoxMask(const sf::IntRect&);
	void setCircleMask( int, int, int );
	CollisionMask* getCollisionMask();
	void setType(std::string);
	std::string getType();
};

#endif
