#ifndef CURSOR_H_
#define CURSOR_H_

#include <SFML/Graphics.hpp>

enum CURSOR_TYPE {ARROW, CROSSHAIR};

class Cursor
{
private:
	sf::Image image_hand;
	sf::Image image_crosshair;
	sf::Sprite sprite_hand;
	sf::Sprite sprite_crosshair;
	sf::Sprite* sprite;
	CURSOR_TYPE type;
public:

	Cursor();
	void Display(sf::RenderWindow*);
	void setType(CURSOR_TYPE);
};

#endif /* CURSOR_H_ */
