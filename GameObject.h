#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "SpriteExt.h"


class GameObject : public Drawable
{
protected:
	int type;
	sf::Image myTexture;
	SpriteExt mySprite;
public:
	GameObject();
	virtual void UpdateSystem();
	virtual void Display(sf::RenderWindow*);
	sf::Vector2f GetPosition();
	int getType();
};

#endif
