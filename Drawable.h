/*
 * Drawable.h
 *
 *
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable
{
protected:
	int depth;
public:
	Drawable();
	virtual ~Drawable();
	virtual void Display(sf::RenderWindow*);
	virtual void UpdateSystem();
	virtual void EventHandling();
	virtual void GetEvents();
	void setDepth(int);
	int getDepth();
};

#endif
