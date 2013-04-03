#ifndef BOXMASK_H
#define BOXMASK_H

#include <SFML/Graphics.hpp>

#include "CollisionMask.h"

class BoxMask : public CollisionMask
{
private:
	sf::IntRect box;
public:
	BoxMask( const sf::IntRect& );
	sf::IntRect& getRect();
	void Display(sf::RenderWindow*, const sf::Vector2f&, const sf::Color = sf::Color(255,255,0));
};

#endif
