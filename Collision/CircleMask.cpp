#include "CircleMask.h"

CircleMask::CircleMask(int _x, int _y, int _radius)
{
	x = _x;
	y = _y;
	radius = _radius;
}

int CircleMask::getX()
{
	return x;
}

int CircleMask::getY()
{
	return y;
}

int CircleMask::getRadius()
{
	return radius;
}

void CircleMask::Display( sf::RenderWindow *window, const sf::Vector2f& pos, const sf::Color color )
{
	sf::Shape circle = sf::Shape::Circle( (pos.x + x),
										  (pos.y + y),
										  radius,
										  sf::Color(0,0,0,0),
										  1.f,
										  color );
	window->Draw(circle);
}
