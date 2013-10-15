#include "Invincibility.h"
#include "../GameEngine.h"
#include "../ImageManager.h"

Invincibility::Invincibility(float x, float y)
{
	image = ImageManager::getInstance()->loadImage("Data/Textures/Powerups/Invincibility.png");
	image.SetSmooth(false);
	sprite.SetImage(image);
    sprite.SetScale( 1, 1 );
    sprite.SetSubRect(sf::IntRect(0,0,32,32));
	sprite.SetPosition( x, y );
	sprite.SetCenter(0,0);
	sprite.setBoxMask(sf::IntRect(1,16,31,32));
	sprite.setType("invincibility");
	active = true;
	deactivate = false;
}

void Invincibility::UpdateSystem()
{
	if (deactivate && Hero::invincible) active = false;
	if (active)
		GameEngine::getInstance()->AddToCollisionQuadtree(&sprite);
}

void Invincibility::EventHandling()
{
	if (active)
	{
		depth = -sprite.GetPosition().y -16;
		if ( GameEngine::getInstance()->DetectCollision(&sprite, "Hero") )
			deactivate = true;
	}
}


void Invincibility::Display(sf::RenderWindow * window)
{
	if (!active) return;
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
