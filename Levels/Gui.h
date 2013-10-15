#include <SFML/Graphics.hpp>
#include "../Drawable.h"
#include "../SpriteExt.h"

#ifndef GUI_H
#define GUI_H

class Gui : public Drawable
{
private:
	bool weaponChanged;
	sf::Image *image;
	SpriteExt *sprite;
	int numberOfWeapons;
	int currentWeapon;
	int screenWidth;
	int screenHeight;
	sf::Vector2f heroPosition;

public:
	Gui(int _screenWidth = 800,int _screenHeight = 600 , sf::Vector2f start = sf::Vector2f(0.0,0.0));
	~Gui(void);
	void SetCurrentWeapon(int weapon);
	void SetHeroPosition( sf::Vector2f _heroPosition );
	void UpdateSystem();
	void Display(sf::RenderWindow*);
};
#endif /* GUI_H */

