#include "Missle.h"

Missle::Missle(float Range ,float Velocity )
:range(Range), velocity(Velocity)
{
	bullet = sf::Shape::Circle(0,0,2.0,sf::Color(255,0,255));	//Ten tymczasowy wygl¹d pocisku
	bullet.SetPosition(0,0);

	inMove   = false;
}

Missle::~Missle(void)
{
}
void Missle::Logic()
{
	inMove = false;
	
	currentPosition = bullet.GetPosition();
	currentDistance = sqrt((startPosition.x-currentPosition.x)*(startPosition.x-currentPosition.x)
						 + (startPosition.y-currentPosition.y)*(startPosition.y-currentPosition.y));
	
	if(currentDistance < range)
	{
	bullet.Move(velocity * (targetPosition.x)/distanceFromTarget, velocity * (targetPosition.y  ) / distanceFromTarget);
	inMove = true;
	}
}
void Missle::SetTarget(sf::Vector2f DesignatedPosition,float DistanceFromMouseClick )
{
	targetPosition	   = DesignatedPosition;
	distanceFromTarget = DistanceFromMouseClick;
}
void Missle::StartPosition(sf::Vector2f Position)
{
	bullet.SetPosition(Position.x,Position.y);
	startPosition = Position;
}
void Missle::Display(sf::RenderWindow *window)
{
	//if(inMove == false) //ukrywanie po skonczonym biegu
	window->Draw( bullet );
}
