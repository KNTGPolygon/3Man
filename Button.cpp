#include "Button.h"
#include "GameEngine.h"
#include "Sfx/SoundPlayer.h"

Button::Button(const sf::Input &_steering,sf::Vector2f _position,sf::Vector2f _size,sf::Color _color,std::string _text)
: color(_color), position(_position), size(_size), steering(_steering), pressed(false)
{
	font.LoadFromFile("Data/Fonts/8-BIT WONDER.ttf");
	text.SetFont( font );
	box   = sf::Shape::Rectangle(0,0,size.x,size.y,color);
	text.SetColor(sf::Color(255,255,255));
	box.SetPosition(position);
	text.SetText( _text );
	text.SetSize( 12 );
	//text.SetCenter(box.GetCenter());
	text.SetCenter(text.GetRect().GetWidth() /2,text.GetRect().GetHeight()/2);
	text.SetPosition(box.GetPosition().x + size.x/2,box.GetPosition().y + size.y/2);
	//text.SetCenter((text.GetRect().GetWidth() - size.x)/2, (text.GetRect().GetHeight() + size.y)/2);
	singlePressed = false;
	pressed = false;
	isMouseOn = false;
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

	if( GameEngine::getInstance()->getEvent().Type == sf::Event::MouseMoved )
		isMouseOn = true;
	
	if(  ( (GameEngine::getInstance()->GetMouseCoords().x) < ( size.x + position.x) && (GameEngine::getInstance()->GetMouseCoords().x) > (position.x) )
	  && ( (GameEngine::getInstance()->GetMouseCoords().y) < ( size.y + position.y) && (GameEngine::getInstance()->GetMouseCoords().y) > (position.y) ))
	
	{
		box.SetColor(sf::Color(255,255,255));
		if( steering.IsMouseButtonDown(sf::Mouse::Left) && isMouseOn )
		{
		
		if( pressed == false )
			singlePressed = true;
		else 
			singlePressed = false;

		pressed = true;
		} else
		{
			pressed = false;
			singlePressed = false;
		}

	}
	if ( singlePressed )
		SoundPlayer::getInstance()->Play(Snd::MenuSelect);
}
void Button::Display(sf::RenderWindow *window)
{
	window->Draw( box );
	window->Draw( text );
}
