#include "GameEngine.h"
#include "GameObject.h"
#include "ImageManager.h"



GameObject::GameObject()
{

}

GameObject::GameObject(float x, float y, int _type, std::string imageFilePath)
{
	//std::cout << imageFilePath << std::endl;
	type = _type;
	myTexture = ImageManager::getInstance()->loadImage(imageFilePath.c_str());
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));
	mySprite.SetImage(myTexture);
    mySprite.SetScale( 1, 1 );
	mySprite.SetSubRect(sf::IntRect(0,0,32,32));
	mySprite.SetPosition( x, y );
	mySprite.SetCenter(0,0);
	mySprite.setBoxMask(sf::IntRect(2,24,30,30));
	mySprite.setType("sth");

	GameEngine::getInstance()->AddToCollisionList(&mySprite);

}

void GameObject::Update()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
	depth = -mySprite.GetPosition().y;
}

void GameObject::Display(sf::RenderWindow * window)
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

sf::Vector2f GameObject::GetPosition()
{
	return mySprite.GetPosition();
}

int GameObject::getType()
{
	return type;
}