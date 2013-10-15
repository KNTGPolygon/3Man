#include "GameActiveObject.h"
#include "GameEngine.h"

GameActiveObject::GameActiveObject()
{

}

GameActiveObject::GameActiveObject(float x, float y, int _type, std::string imageFilePath)
{
	targetingHero = false;
	targetRotationAndDirection.x = 90;
	targetRotationAndDirection.y = 1;
	rotationCooldown = 0;

	std::string objectPath = "Data/Textures/MapObjects/";
	type = _type;
	myTexture = ImageManager::getInstance()->loadImage((objectPath + imageFilePath).c_str());
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));
	myTexture.SetSmooth(false);

	int textureHeight = myTexture.GetHeight();

	mySprite.SetImage(myTexture);
    mySprite.SetScale( 1, 1 );
	mySprite.SetPosition( x + 16, y + 16);
	mySprite.SetCenter(16,textureHeight/2);
	mySprite.setBoxMask(sf::IntRect(2, textureHeight - 30 ,30,textureHeight));
	mySprite.setType("wall");


	upTexture = ImageManager::getInstance()->loadImage((objectPath + "Up" + imageFilePath).c_str());
	upTexture.CreateMaskFromColor(sf::Color(255,0,255));
	upTexture.SetSmooth(false);

	textureHeight = upTexture.GetHeight();

	upSprite.SetImage(upTexture);
    upSprite.SetScale( 1, 1 );
	upSprite.SetPosition( x + 16, y + 16);
	upSprite.SetCenter(16,textureHeight/2);
	upSprite.setBoxMask(sf::IntRect(2, textureHeight - 30 ,30,textureHeight));
	upSprite.setType("wall");

}

void GameActiveObject::UpdateSystem()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
}

void GameActiveObject::EventHandling()
{
	depth = -mySprite.GetPosition().y;

	sf::Vector2f heroPosition = Hero::myPosition;

	if(targetingHero == false)
		doSomeAnimations();

}

void GameActiveObject::doSomeAnimations()
{
	if(upSprite.GetRotation() != targetRotationAndDirection.x && rotationCooldown <= 0)
		{
			upSprite.Rotate(targetRotationAndDirection.y);
		}
		else if(rotationCooldown <= 0)
		{
			doSomeAnimations_DecideOnNewTargetAngle();
			doSomeAnimations_CountShortestRotationPath();
		}
		else
		{
			rotationCooldown--;
		}
}

void GameActiveObject::doSomeAnimations_CountShortestRotationPath()
{
	rotationCooldown = rand() % 300;

			int distanceToAngle = targetRotationAndDirection.x - upSprite.GetRotation();

			if( distanceToAngle > 0)
			{
				if(distanceToAngle < 180)
				{
					targetRotationAndDirection.y = 1;
				}
				else
				{
					targetRotationAndDirection.y = -1;
				}
			}
			else
			{
				if(-distanceToAngle < 180)
				{
					targetRotationAndDirection.y = -1;
				}
				else
				{
					targetRotationAndDirection.y = 1;
				}
			}
}

void GameActiveObject::doSomeAnimations_DecideOnNewTargetAngle()
{
	targetRotationAndDirection.x = (rand() % 4) * 90;
}


void GameActiveObject::Display(sf::RenderWindow * window)
{
	
	window->Draw(mySprite);
	window->Draw(upSprite);
	
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

