#include "Missle.h"

Missle::Missle(std::string fileName, float Range ,float Velocity )
:range(Range), velocity(Velocity)
{
	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Weapons/"+fileName );
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));
	mySprite.SetImage(myTexture);
	mySprite.SetPosition(0,0);
	mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
	strAngle.SetPosition(50.0,300.0);
	
	angle = 0;
	inMove   = false;
	
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
	
	if(currentDistance < range)
	{
	if(targetPosition.x > 0)
	angle = 90+ asin ( ( ( (-targetPosition.y)/distanceFromTarget))) * (180.0 / PI);
	else
	angle = 90+ asin ( ( ( (+targetPosition.y)/distanceFromTarget))) * (180.0 / PI);
	strAngle.SetText( "angle = "+flo2str(angle)  );
	mySprite.SetRotation(angle );
	mySprite.Move(velocity * (targetPosition.x)/distanceFromTarget, velocity * (targetPosition.y  ) / distanceFromTarget);
	inMove = true;
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
	//if(inMove == false) //ukrywanie po skonczonym biegu
	window->Draw( mySprite );
}
