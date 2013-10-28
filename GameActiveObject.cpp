#include "GameActiveObject.h"
#include "GameEngine.h"

GameActiveObject::GameActiveObject()
{

}

GameActiveObject::GameActiveObject(float x, float y, int _type, std::string imageFilePath, int ** arrayOfFieldsOccupiedWithObj, int objectArraySize)
{
	arrayOfFieldsOccupiedWithObjects = arrayOfFieldsOccupiedWithObj;
	arrayOfOccupiedFieldsSize = objectArraySize;

	targetingHero = false;
	chargingAttack = false;

	distanceOfHeroTargeting = 150;

	targetRotationAndDirection.x = 90;
	targetRotationAndDirection.y = 1;
	rotationCooldown = 0;

	shootCooldown = 0;
	laserExistanceTime = 0;
	shootDirection.x = 0;
	shootDirection.x = 0;

	std::string objectPath = "Data/Textures/MapObjects/";
	type = _type;
	myTexture = ImageManager::getInstance()->loadImage((objectPath + imageFilePath).c_str());
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));
	myTexture.SetSmooth(false);

	int textureHeight = myTexture.GetHeight();

	mySprite.SetImage(myTexture);
    mySprite.SetScale( 1, 1 );
	mySprite.SetPosition( x + 16, y + 16);
	mySprite.SetCenter((float)16,(float)(textureHeight/2));
	mySprite.setBoxMask(sf::IntRect(2, textureHeight - 30 ,30,textureHeight));
	mySprite.setType("wall");

	//--------------------------------------------------
	upTexture = ImageManager::getInstance()->loadImage((objectPath + "Up" + imageFilePath).c_str());
	upTexture.CreateMaskFromColor(sf::Color(255,0,255));
	upTexture.SetSmooth(false);

	textureHeight = upTexture.GetHeight();

	upSprite.SetImage(upTexture);
    upSprite.SetScale( 1, 1 );
	upSprite.SetPosition( x + 16, y + 16);
	upSprite.SetCenter((float)16,(float)(textureHeight/2));
	upSprite.setBoxMask(sf::IntRect(2, textureHeight - 30 ,30,textureHeight));
	upSprite.setType("wall");

	//--------------------------------------------
	if(type == 1)
	{
		trapType = BULLET_TOWER;
	}
	else if(type == 0)
	{
		trapType = LASER_TOWER;
	}
	else
	{
		trapType = SPIKES;
	}

	//-------------------------------------------------
	std::string ammoPath = "Data/Textures/Weapons/";
	if(trapType == BULLET_TOWER)
		shotTexture = ImageManager::getInstance()->loadImage((ammoPath + "Plus.png").c_str());
	else if (trapType == LASER_TOWER)
		shotTexture = ImageManager::getInstance()->loadImage((ammoPath + "Lazer.png").c_str());

	shotTexture.CreateMaskFromColor(sf::Color(255,0,255));
	shotTexture.SetSmooth(false);

	shotSprite.SetImage(shotTexture);
    shotSprite.SetScale( 1, 1 );
	shotSprite.SetPosition( x + 16, y + 16);
	shotSprite.SetCenter((float)16,(float)(textureHeight/2));
	shotSprite.setType("Lazer");


}

void GameActiveObject::UpdateSystem()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
	
}

void GameActiveObject::EventHandling()
{
	depth = (int)(-mySprite.GetPosition().y);

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
	

	if(distanceOfHeroTargeting * distanceOfHeroTargeting > distanceBetweenHeroAndTrap.x * distanceBetweenHeroAndTrap.x + distanceBetweenHeroAndTrap.y * distanceBetweenHeroAndTrap.y && chargingAttack == false)
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
	if(chargingAttack == false)
	{
		if(upSprite.GetRotation() != targetRotationAndDirection.x && rotationCooldown <= 0)
			{
				upSprite.Rotate((float)targetRotationAndDirection.y);
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
	else
	{
		if(shootCooldown <= 0)
		{
			if(upSprite.GetRotation() == 0)
			{
				shootDirection.y = -1;
			}
			else if(upSprite.GetRotation() == 90)
			{
				shootDirection.x = -1;
			}
			else if(upSprite.GetRotation() == 180)
			{
				shootDirection.y = 1;
			}
			else if(upSprite.GetRotation() == 270)
			{
				shootDirection.x = 1;
			}

			if(laserExistanceTime <= 0)
				chargingAttack = false;
		}
		else
		{
			shootCooldown--;
		}
	}
}

void GameActiveObject::targetHero(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns)
{
	targetHero_decideOnAngle(distanceBetweenHeroAndTrap, distanceSigns);
	doSomeAnimations_CountShortestRotationPath();

	if(upSprite.GetRotation() != targetRotationAndDirection.x && chargingAttack == false)
	{
		upSprite.Rotate((float)targetRotationAndDirection.y);
	}
	else
	{
		if(distanceBetweenHeroAndTrap.x <= 1 || distanceBetweenHeroAndTrap.y <= 1)
		{
			chargingAttack = true;
			laserExistanceTime = 100;
			shootCooldown = 100;
		}
	}
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

void GameActiveObject::attackHero()
{
	if(upSprite.GetRotation() == 90 || upSprite.GetRotation() == 270)
	{
		shotSprite.SetRotation(90);
	}
	else
	{
		shotSprite.SetRotation(0);
	}
}

void GameActiveObject::doSomeAnimations_CountShortestRotationPath()
{

			int distanceToAngle = targetRotationAndDirection.x - (int)upSprite.GetRotation();

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

	if(chargingAttack == true)
		{
			sf::Color color = upSprite.GetColor();
			color.a = 200;
			upSprite.SetColor(color);
		}
	else
		{
			sf::Color color = upSprite.GetColor();
			color.a = 255;

			upSprite.SetColor(color);
		}
	
	window->Draw(mySprite);
	window->Draw(upSprite);

	if(shootDirection.x != 0 || shootDirection.y != 0)
	{
		if(upSprite.GetRotation() == 90 || upSprite.GetRotation() == 270)
			shotSprite.SetRotation(90);
		else
			shotSprite.SetRotation(0);

		int numberOfFieldsToDraw = Display_howLongShouldTheLaserBe();

		for(int multipler = 1; multipler <= numberOfFieldsToDraw;multipler++)
		{
			shotSprite.SetPosition( upSprite.GetPosition().x + 32 * shootDirection.x * multipler, upSprite.GetPosition().y + 32 * shootDirection.y * multipler);
			window->Draw(shotSprite);
		
		}

		sf::Vector2f heroPosition = Hero::myPosition;
		if(numberOfFieldsToDraw > 0)
		{
			if(heroPosition.x > upSprite.GetPosition().x - 2 && heroPosition.x < upSprite.GetPosition().x + 2)
			{
				if(upSprite.GetRotation() == 180 && (upSprite.GetPosition().y < heroPosition.y))
					Hero::getHitByLaser();
				else if(upSprite.GetRotation() == 0 && (upSprite.GetPosition().y > heroPosition.y))
					Hero::getHitByLaser();
			}
			else if(heroPosition.y > upSprite.GetPosition().y - 2 && heroPosition.y < upSprite.GetPosition().y + 2)
			{
				if(upSprite.GetRotation() == 270 && (upSprite.GetPosition().x < heroPosition.x))
					Hero::getHitByLaser();
				else if(upSprite.GetRotation() == 90 && (upSprite.GetPosition().x > heroPosition.x))
					Hero::getHitByLaser();
			}
		}

		if(laserExistanceTime <= 0)
		{
			shootDirection.x = 0;
			shootDirection.y = 0;
		}
		else
		{
			laserExistanceTime--;
		}
	}
	
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

int GameActiveObject::Display_howLongShouldTheLaserBe()
	{
		int numberOfFieldsToDraw = 0;

		if(shootDirection.x > 0 || shootDirection.y > 0)
		{
			for( int row = (int)((upSprite.GetPosition().y - 16)/32); row < arrayOfOccupiedFieldsSize; row)
				{
					for( int col = (int)((upSprite.GetPosition().x - 16)/32); col < arrayOfOccupiedFieldsSize; col)
					{
						row += shootDirection.y;
						col += shootDirection.x;
						if(arrayOfFieldsOccupiedWithObjects[row][col] != 1)
						{
							numberOfFieldsToDraw++;
						}
						else
						{
							col = arrayOfOccupiedFieldsSize;
							row = arrayOfOccupiedFieldsSize;
							break;
						}
					}
				}
		}
		else
		{
			for( int row = (int)((upSprite.GetPosition().y - 16)/32); row > 0; row)
				{
					for( int col = (int)((upSprite.GetPosition().x - 16)/32); col > 0; col)
					{
						row += shootDirection.y;
						col += shootDirection.x;
						if(arrayOfFieldsOccupiedWithObjects[row][col] != 1)
						{
							numberOfFieldsToDraw++;
						}
						else
						{
							col = 0;
							row = 0;
							break;
						}
					}
				}
		}

		return numberOfFieldsToDraw;
	}
