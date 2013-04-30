#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "SpriteExt.h"

class GameObject : public Drawable
{
private:
	int type;
	sf::Image myTexture;
	SpriteExt mySprite;
public:
	GameObject();
	GameObject(float, float, int _type, std::string imageFilePath);
	void Update();
	void Display(sf::RenderWindow*);
	sf::Vector2f GetPosition();
	int getType();
};

#endif
