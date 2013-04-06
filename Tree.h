#ifndef TREE_H
#define TREE_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "SpriteExt.h"

class Tree : public Drawable
{
private:
	sf::Image myTexture;
	SpriteExt mySprite;
public:
	Tree(float, float);
	void Update();
	void Display(sf::RenderWindow*);
};

#endif
