#include "GameActiveObject.h"
#include "GameEngine.h"

GameActiveObject::GameActiveObject()
{

}

GameActiveObject::GameActiveObject(float x, float y, int _type, std::string imageFilePath)
{
	type = _type;
	myTexture = ImageManager::getInstance()->loadImage(imageFilePath.c_str());
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));
	myTexture.SetSmooth(false);

	int textureHeight = myTexture.GetHeight();

	mySprite.SetImage(myTexture);
    mySprite.SetScale( 1, 1 );
	mySprite.SetPosition( x - 16, y - 16);
	mySprite.SetCenter(16,textureHeight/2);
	mySprite.setBoxMask(sf::IntRect(2, textureHeight - 8 ,30,textureHeight));
	mySprite.setType("wall");

}

void GameActiveObject::UpdateSystem()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
}

void GameActiveObject::EventHandling()
{
	depth = -mySprite.GetPosition().y;
}

void GameActiveObject::Display(sf::RenderWindow * window)
{
	
	window->Draw(mySprite);
	
	if(GameEngine::getInstance()->devmode)
	{
		if ( GameEngine::getInstance()->DetectCollision(&mySprite) )
		((BoxMask*)mySprite.getCollisionMask())->Display(window,
														 sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x,
																	  mySprite.GetPosition().y-mySprite.GetCenter().y), sf::Color(255,0,0));
		else
		((BoxMask*)mySprite.getCollisionMask())->Display(window,
														 sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x,
																	  mySprite.GetPosition().y-mySprite.GetCenter().y));
	}

}

