#pragma once
//#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include <string>
#include "Util.h"

class InputBox : public Drawable
{
private:
	std::string		textString;
	std::string		tempTextString;

	sf::Color		color;
	sf::String		text;
	sf::Shape		box;
	sf::Shape		karetka;
	sf::Vector2f	position;
	sf::Vector2f	size;
	sf::Clock		timer;
	sf::Clock		karetkaTime;
	sf::Uint32		lastSymbolEntered;
	
	int stringShift;
	int stringLength;

	bool active;
	bool karetkaVisable;
	bool typing;
	bool shifted;
	bool singleKeyPress;
	bool keyHolded;

	float lastTime;
	float currentTime;
	float textSize;
	float karetkaBlinkTime;

	static	const int TEXT_SHIFT = 5;
	const sf::Input &steering;
public:
	InputBox(const sf::Input &_steering,sf::Vector2f _position, std::string defaultInboxText = "Wprowadz text", sf::Vector2f _size = sf::Vector2f(200,30));
	~InputBox(void);

	void HandleEvent(sf::Event event);
	void Display(sf::RenderWindow *window);
	void SetFontSize(int Size);
	std::string GetString();

};

