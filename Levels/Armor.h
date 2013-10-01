#ifndef ARMOR_H_
#define ARMOR_H_

#include <SFML/Graphics.hpp>
#include "../Drawable.h"
#include "../SpriteExt.h"

class Armor : public Drawable
{
private:
	sf::Image image;
	SpriteExt sprite;
public:
	void UpdateSystem();
	void EventHandling();
	void Display(sf::RenderWindow*);
};

#endif /* ARMOR_H_ */
