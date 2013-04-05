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
	void setDepth(int);
	int getDepth();
};

#endif
