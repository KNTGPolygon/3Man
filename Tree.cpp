#include "GameEngine.h"
#include "Tree.h"
#include "ImageManager.h"

Tree::Tree(float x, float y)
{
	myTexture = ImageManager::getInstance()->loadImage("Data/Textures/Object_Trees.png");
	mySprite.SetImage(myTexture);
    mySprite.SetScale( 1, 1 );
	mySprite.SetSubRect(sf::IntRect(0,0,105,130));
	mySprite.SetPosition( x, y );
	mySprite.SetCenter(48,115);
	mySprite.setBoxMask(sf::IntRect(26,103,72,120));

	GameEngine::getInstance()->AddToCollisionList(&mySprite);
}

void Tree::Update()
{
	depth = -mySprite.GetPosition().y;
}

void Tree::Display(sf::RenderWindow * window)
{
	window->Draw(mySprite);
	((BoxMask*)mySprite.getCollisionMask())->Display(window, sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x, mySprite.GetPosition().y-mySprite.GetCenter().y));
}
