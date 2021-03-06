#pragma once
#include <SFML/Graphics.hpp>

class TextBox
{
protected:
	sf::Color color;
	sf::String text;
	sf::Shape box;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Font font;

public:
	TextBox(sf::Vector2f _position = sf::Vector2f(0.0,0.0),
			sf::Vector2f _size = sf::Vector2f(0.0,0.0),
			sf::Color _color = sf::Color(125,125,125),
			std::string _text = "");
	~TextBox(void);
	void SetPosition(sf::Vector2f newPosition);
	void SetText(std::string Text);
	void SetTextPosition(sf::Vector2f newPosition);
	void SetFontSize(float FontSize);
	void SetTextColor(sf::Color Color);
	sf::Vector2f GetTextBoxPosition();
	sf::String GetText();
	void Display(sf::RenderWindow *window);
};
