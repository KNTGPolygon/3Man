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
	mySprite.SetPosition( x, y );
	mySprite.SetCenter(0,0);
	mySprite.setBoxMask(sf::IntRect(2, textureHeight - 8 ,30,textureHeight));
	mySprite.setType("active object");

}

void GameActiveObject::Update()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
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

