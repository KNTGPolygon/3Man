#include "Button.h"

Button::Button(const sf::Input &_steering,sf::Vector2f _position,sf::Vector2f _size,sf::Color _color,std::string _text)
: steering(_steering), position(_position), size(_size),pressed(false),color(_color)
{

	box   = sf::Shape::Rectangle(0,0,size.x,size.y,color);
	text.SetColor(sf::Color(255,255,255));
	box.SetPosition(position);
	text.SetPosition(box.GetPosition());
	text.SetText( _text );
	text.SetCenter(box.GetCenter());
}

Button::~Button(void)
{
}
void Button::SetPosition(sf::Vector2f newPosition)
{
	box.SetPosition(newPosition);
}
void Button::GetEvent()
{
		box.SetColor(color);

	if(  ( steering.GetMouseX() < ( size.x + position.x) && steering.GetMouseX() > (position.x) )
	  && ( steering.GetMouseY() < ( size.y + position.y) && steering.GetMouseY() > (position.y) ))
	{
		box.SetColor(sf::Color(255,255,255));
		if(steering.IsMouseButtonDown(sf::Mouse::Left))
		{
		pressed = true;
		}
	}
}
void Button::Display(sf::RenderWindow *window)
{
	window->Draw( box );
	window->Draw( text );
}
