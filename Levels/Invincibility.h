#ifndef INVINCIBILITY_H_
#define INVINCIBILITY_H_

#include <SFML/Graphics.hpp>
#include "../Drawable.h"
#include "../SpriteExt.h"

class Invincibility : public Drawable
{
private:
	sf::Image image;
	SpriteExt sprite;
	bool active;
	bool deactivate;
public:
	Invincibility(float, float);
	void UpdateSystem();
	void EventHandling();
	void Display(sf::RenderWindow*);
};

#endif /* INVINCIBILITY_H_ */
