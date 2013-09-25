#ifndef WALL_H_
#define WALL_H_

#include <SFML/Graphics.hpp>
#include "../Drawable.h"
#include "../SpriteExt.h"

class Wall : public Drawable
{
private:
	sf::Image image;
	SpriteExt sprite;
public:
	Wall(float, float);
	void Display(sf::RenderWindow*);
	void EventHandling();
	void UpdateSystem();
};

#endif /* WALL_H_ */
