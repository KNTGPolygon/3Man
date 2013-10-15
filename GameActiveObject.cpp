#include "GameActiveObject.h"
#include "GameEngine.h"

GameActiveObject::GameActiveObject()
{

}

GameActiveObject::GameActiveObject(float x, float y, int _type, std::string imageFilePath)
{
	targetingHero = false;
	distanceOfHeroTargeting = 150;

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
	sf::Vector2f trapPosition = mySprite.GetPosition();

	sf::Vector2f distanceBetweenHeroAndTrap;
	sf::Vector2i signsOfDistances;

	if(heroPosition.x - trapPosition.x >= 0)
	{
		distanceBetweenHeroAndTrap.x =  heroPosition.x - trapPosition.x;
		signsOfDistances.x = -1;
	}
	else
	{
		distanceBetweenHeroAndTrap.x =  trapPosition.x - heroPosition.x;
		signsOfDistances.x = 1;
	}

	if(heroPosition.y - trapPosition.y >= 0)
	{
		distanceBetweenHeroAndTrap.y = heroPosition.y - trapPosition.y;
		signsOfDistances.y = -1;
	}
	else
	{
		distanceBetweenHeroAndTrap.y = trapPosition.y - heroPosition.y;
		signsOfDistances.y = 1;
	}
	

	if(distanceOfHeroTargeting * distanceOfHeroTargeting > distanceBetweenHeroAndTrap.x * distanceBetweenHeroAndTrap.x + distanceBetweenHeroAndTrap.y * distanceBetweenHeroAndTrap.y)
	{
		targetHero(distanceBetweenHeroAndTrap, signsOfDistances);
	}
	else
	{
		doSomeAnimations();
	}
		

}

void GameActiveObject::doSomeAnimations()
{
	if(upSprite.GetRotation() != targetRotationAndDirection.x && rotationCooldown <= 0)
		{
			upSprite.Rotate(targetRotationAndDirection.y);
		}
		else if(rotationCooldown <= 0)
		{
			rotationCooldown = rand() % 300;

			doSomeAnimations_DecideOnNewTargetAngle();
			doSomeAnimations_CountShortestRotationPath();
		}
		else
		{
			rotationCooldown--;
		}
}

void GameActiveObject::targetHero(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns)
{
	targetHero_decideOnAngle(distanceBetweenHeroAndTrap, distanceSigns);
	doSomeAnimations_CountShortestRotationPath();
	upSprite.Rotate(targetRotationAndDirection.y);
}

void GameActiveObject::targetHero_decideOnAngle(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns)
{
	if(distanceSigns.x == 1 && distanceSigns.y == 1)
	{
		if(distanceBetweenHeroAndTrap.x >= distanceBetweenHeroAndTrap.y)
		{
			targetRotationAndDirection.x = 90;
		}
		else
		{
			targetRotationAndDirection.x = 0;
		}
	}
	else if (distanceSigns.x == 1 && distanceSigns.y == -1)
	{
		if(distanceBetweenHeroAndTrap.x >= distanceBetweenHeroAndTrap.y)
		{
			targetRotationAndDirection.x = 90;
		}
		else
		{
			targetRotationAndDirection.x = 180;
		}
	}
	else if (distanceSigns.x == -1 && distanceSigns.y == 1)
	{
		if(distanceBetweenHeroAndTrap.x >= distanceBetweenHeroAndTrap.y)
		{
			targetRotationAndDirection.x = 270;
		}
		else
		{
			targetRotationAndDirection.x = 0;
		}
	}
	else if (distanceSigns.x == -1 && distanceSigns.y == -1)
	{
		if(distanceBetweenHeroAndTrap.x >= distanceBetweenHeroAndTrap.y)
		{
			targetRotationAndDirection.x = 270;
		}
		else
		{
			targetRotationAndDirection.x = 180;
		}
	}
}

void GameActiveObject::targetHero_checkWhichWayToTurn()
{
	
}

void GameActiveObject::doSomeAnimations_CountShortestRotationPath()
{

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

