#include "Invincibility.h"
#include "../GameEngine.h"
#include "../ImageManager.h"

Invincibility::Invincibility(float x, float y)
{
	image = ImageManager::getInstance()->loadImage("Data/Textures/MapObjects/Wall.png");
	image.SetSmooth(false);
	sprite.SetImage(image);
    sprite.SetScale( 1, 1 );
    sprite.SetSubRect(sf::IntRect(0,0,32,64));
	sprite.SetPosition( x, y );
	sprite.SetCenter(0,32);
	sprite.setBoxMask(sf::IntRect(1,33,31,64));
	sprite.setType("invincibility");
}

void Invincibility::UpdateSystem()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&sprite);
}

void Invincibility::EventHandling()
{
	depth = -sprite.GetPosition().y;
}


void Invincibility::Display(sf::RenderWindow * window)
{
	window->Draw(sprite);

	if(GameEngine::getInstance()->devmode)
	{
		if ( GameEngine::getInstance()->DetectCollision(&sprite) )
		((BoxMask*)sprite.getCollisionMask())->Display(window,
														 sf::Vector2f(sprite.GetPosition().x-sprite.GetCenter().x,
																	  sprite.GetPosition().y-sprite.GetCenter().y), sf::Color(255,0,0));
		else
		((BoxMask*)sprite.getCollisionMask())->Display(window,
														 sf::Vector2f(sprite.GetPosition().x-sprite.GetCenter().x,
																	  sprite.GetPosition().y-sprite.GetCenter().y));
	}
}
