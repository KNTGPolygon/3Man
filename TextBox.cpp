#include "TextBox.h"

TextBox::TextBox(sf::Vector2f _position,sf::Vector2f _size,sf::Color _color,std::string _text)
: color(_color), position(_position), size(_size)
{
	font.LoadFromFile("Data/Fonts/8-BIT WONDER.ttf");
	//text.SetFont( font );
	box   = sf::Shape::Rectangle(0,0,size.x,size.y,color);
	box.SetPosition(position);

	text.SetColor(sf::Color(0,0,0));
	text.SetText( _text );
	//text.SetCenter(text.GetRect().GetWidth() /2,text.GetRect().GetHeight()/2);
	//text.SetPosition(box.GetPosition().x + size.x/2,box.GetPosition().y + size.y/2);
	text.SetPosition(box.GetPosition().x, box.GetPosition().y);
	text.SetSize(20.0);
}

TextBox::~TextBox(void)
{
}	
void TextBox::SetTextColor(sf::Color Color)
{
	text.SetColor( Color );
}
void TextBox::SetFontSize(float FontSize)
{
	text.SetSize( FontSize );
}
void TextBox::SetText(std::string Text)
{
	text.SetText(Text);
}
void TextBox::SetTextPosition( sf::Vector2f newPosition )
{
	text.SetPosition( newPosition );
}
void TextBox::SetPosition(sf::Vector2f newPosition)
{
	box.SetPosition(newPosition);
}
sf::Vector2f TextBox::GetTextBoxPosition()
{
	return position;
}
sf::String TextBox::GetText()
{
	return text;
}
void TextBox::Display(sf::RenderWindow *window)
{
	window->Draw( box );
	window->Draw( text );
}
