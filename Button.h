#pragma once
#include <SFML/Graphics.hpp>

#ifndef BUTTON_H
#define BUTTON_H
class Button
{
private:

	sf::Color color;
	sf::String text;
	sf::Shape box;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Font font;

	const sf::Input &steering;
public:
	bool pressed;
	bool singlePressed;
	Button(const sf::Input &_steering,sf::Vector2f _position,sf::Vector2f _size,sf::Color _color,std::string _text);
	void SetPosition(sf::Vector2f newPosition);
	~Button(void);
	void GetEvent();
	void Display(sf::RenderWindow *window);
};

#endif
