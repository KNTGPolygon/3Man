#include "Wall.h"
#include "../GameEngine.h"
#include "../ImageManager.h"

Wall::Wall(float x, float y)
{
	image = ImageManager::getInstance()->loadImage("Data/Textures/MapObjects/Wall.png");
	image.SetSmooth(false);
	sprite.SetImage(image);
    sprite.SetScale( 1, 1 );
    sprite.SetSubRect(sf::IntRect(0,0,32,48));
	sprite.SetPosition( x, y );
	sprite.SetCenter(0,16);
	sprite.setBoxMask(sf::IntRect(1,33,31,48));
	sprite.setType("wall");
}

void Wall::UpdateCollision()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&sprite);
}

void Wall::Update()
{
	depth = -sprite.GetPosition().y;
}


void Wall::Display(sf::RenderWindow * window)
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

