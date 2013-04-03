#include "BoxMask.h"

BoxMask::BoxMask( const sf::IntRect& _box )
{
	box.Bottom = _box.Bottom;
	box.Left = _box.Left;
	box.Right = _box.Right;
	box.Top = _box.Top;
	type = BOX;
}

sf::IntRect& BoxMask::getRect()
{
	return box;
}

void BoxMask::Display( sf::RenderWindow *window, const sf::Vector2f& pos, const sf::Color color )
{
	sf::Shape rect = sf::Shape::Rectangle(((float)pos.x + box.Left),
										  ((float)pos.y + box.Top),
										  ((float)pos.x + box.Right),
										  ((float)pos.y + box.Bottom),
										  sf::Color(0,0,0,0),
										  1.f,
										  color );
	window->Draw(rect);
}
