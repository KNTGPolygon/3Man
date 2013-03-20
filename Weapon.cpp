#include "Weapon.h"

Weapon::Weapon(const sf::Input &_steering,int BulletFireLimit,float RepeatRate)
:steering(_steering) ,bulletFireLimit(BulletFireLimit), repeatRate(RepeatRate)
{
	SCREEN_WIDTH  = 800; 
	SCREEN_HEIGHT = 600;
	missle = new Missle*[(bulletFireLimit-1)];

	for(int i=0;i<bulletFireLimit;i++)
	{
		missle[i] = new Missle(300.0,4.0);
	}

	fired = false;
}

Weapon::~Weapon(void)
{
	delete[] missle;
}
void Weapon::Logic()
{

	if(steering.IsMouseButtonDown(sf::Mouse::Left) && fired == true)
	{
		if(repetition.GetElapsedTime()>repeatRate)
		{
			repetition.Reset();
			destenation.x = (float)steering.GetMouseX()  - SCREEN_WIDTH/2 ;
			destenation.y = (float)steering.GetMouseY()  - SCREEN_HEIGHT/2 ;
			distanceFromMouse=sqrt((float)(destenation.x)*(destenation.x)+(float)(destenation.y)*(destenation.y));
			missle[ReturnFirstAvailable(missle,5)]->StartPosition(fireFromPosition);
			missle[ReturnFirstAvailable(missle,5)]->SetTarget(destenation,distanceFromMouse);
			missle[ReturnFirstAvailable(missle,5)]->inMove = true;
		}
	
	}
		if(steering.IsMouseButtonDown(sf::Mouse::Left) && fired == false)
	{
		repetition.Reset();
		destenation.x = (float)steering.GetMouseX()  - SCREEN_WIDTH/2 ;
		destenation.y = (float)steering.GetMouseY()  - SCREEN_HEIGHT/2 ;
		distanceFromMouse=sqrt((float)(destenation.x)*(destenation.x)+(float)(destenation.y)*(destenation.y));
		missle[0]->StartPosition(fireFromPosition);
		missle[0]->SetTarget(destenation,distanceFromMouse);
		missle[0]->inMove = true;
		fired = true;
	}
		
	fired = false;

	for(int i = 0;i<bulletFireLimit;i++)
	{
		if(missle[i]->inMove == true)
		{
			missle[i]->Logic();
			fired = true;
		}
	}
}
void Weapon::Display(sf::RenderWindow *window)
{
		for(int i =0; i < bulletFireLimit ; i++)
	{
		missle[i]->Display(window);
	}
}

int Weapon::ReturnFirstAvailable(Missle **missle,int MissleAmount )
{
	for(int i = 0 ; i < MissleAmount ; i++)
	{
		if(missle[i]->inMove == false)
		{
			return i;
		}
	}
	return 0;
}
void Weapon::SetFiringPosition(sf::Vector2f Position)
{
	fireFromPosition = Position;
}
void Weapon::PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	SCREEN_WIDTH = _SCREEN_WIDTH; 
	SCREEN_HEIGHT = _SCREEN_HEIGHT;
}
