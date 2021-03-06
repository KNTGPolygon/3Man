#include "GameNonActiveObject.h"
#include "GameEngine.h"

GameNonActiveObject::GameNonActiveObject()
{

}

GameNonActiveObject::GameNonActiveObject(float x, float y, int _type, std::string imageFilePath)
{
	type = _type;
	myTexture = ImageManager::getInstance()->loadImage(imageFilePath.c_str());
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));
	myTexture.SetSmooth(false);

	int textureHeight = myTexture.GetHeight();

	mySprite.SetImage(myTexture);
    mySprite.SetScale( 1, 1 );
	mySprite.SetPosition( x, y);
	mySprite.SetCenter((float)16,(float)(textureHeight/2));
	mySprite.setBoxMask(sf::IntRect(2, textureHeight - 8 ,30,textureHeight));
	mySprite.setType("wall");

}

void GameNonActiveObject::UpdateSystem()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
}

void GameNonActiveObject::EventHandling()
{
	depth = (int)(-mySprite.GetPosition().y);
}

void GameNonActiveObject::Display(sf::RenderWindow * window)
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
