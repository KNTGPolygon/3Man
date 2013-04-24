#ifndef CIRCLEMASK_H
#define CIRCLEMASK_H

#include <SFML/Graphics.hpp>

#include "CollisionMask.h"

class CircleMask : public CollisionMask
{
private:
	int x;
	int y;
	int radius;
public:
	CircleMask(int,int,int);
	int getX();
	int getY();
	int getRadius();
	void Display(sf::RenderWindow*, const sf::Vector2f&, const sf::Color = sf::Color(255,255,0));
};

#endif
