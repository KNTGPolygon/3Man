#include "Missle.h"
#include "GameEngine.h"

Missle::Missle(std::string fileName, float Range ,float Velocity )
:range(Range), velocity(Velocity)
{
	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Weapons/"+fileName );
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));

	mySprite.SetImage(myTexture);
	mySprite.SetPosition(0,0);
	mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
	mySprite.setCircleMask(mySprite.GetCenter().x, mySprite.GetCenter().y, 4);
	mySprite.setType("missile");

	angle = 0;
	inMove   = false;	
	colisionWithiObiect = false;
}

Missle::~Missle(void)
{
}
void Missle::Logic()
{
	inMove = false;

	currentPosition = mySprite.GetPosition();
	currentDistance = sqrt((startPosition.x-currentPosition.x)*(startPosition.x-currentPosition.x)
						 + (startPosition.y-currentPosition.y)*(startPosition.y-currentPosition.y));
	
	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);

	if(currentDistance < range)
	{
		if(targetPosition.x > 0)
		angle = 90+ asin ( ( ( (-targetPosition.y)/distanceFromTarget))) * (180.0 / PI);
		else
		angle = 90+ asin ( ( ( (+targetPosition.y)/distanceFromTarget))) * (180.0 / PI);
		mySprite.SetRotation(angle );

		mySprite.Move(velocity * (targetPosition.x)/distanceFromTarget, velocity * (targetPosition.y  ) / distanceFromTarget);		
		if ( !colisionWithiObiect ) inMove = true;

	}
	if( inMove == false )
	{
		currentPosition.x = 0.0;
		currentPosition.y = 0.0;
		mySprite.SetPosition( currentPosition );
	}
}
void Missle::SetTarget(sf::Vector2i DesignatedPosition,float DistanceFromMouseClick )
{
	targetPosition	   = DesignatedPosition;
	distanceFromTarget = DistanceFromMouseClick;
}
void Missle::StartPosition(sf::Vector2f Position)
{
	mySprite.SetPosition(Position.x,Position.y);
	startPosition = Position;
}
void Missle::Display(sf::RenderWindow *window)
{
	if(inMove != false)			//ukrywanie po skonczonym biegu
	window->Draw( mySprite );
	colisionWithiObiect = false;
	if(GameEngine::getInstance()->devmode)
	{
		if ( GameEngine::getInstance()->DetectCollision(&mySprite) )
		{
			((CircleMask*)mySprite.getCollisionMask())->Display(window,
													   sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x,
																	mySprite.GetPosition().y-mySprite.GetCenter().y),
													   sf::Color(255, 0, 0));
		}
		else
			((CircleMask*)mySprite.getCollisionMask())->Display(window,
													   sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x,
																	mySprite.GetPosition().y-mySprite.GetCenter().y));
		if( GameEngine::getInstance()->DetectCollision(&mySprite,"enemy") ) 
		{
			colisionWithiObiect = true;
			std::cout<<"Wykryto kolizje z enemy w display\n";
		}
		
	}
	
}
float Missle::ReturnAngle()
{
	return angle;
}
