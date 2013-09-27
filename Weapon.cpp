#include "GameEngine.h"
#include "Weapon.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Util.h"

Weapon::Weapon(WeaponType weaponType , int BulletFireLimit,float RepeatRate)
:bulletFireLimit(BulletFireLimit), repeatRate(RepeatRate)
{
	directory = "Integral.PNG";
	missleColider = "enemy";
	damage = 1;
	range = 1;
	speed = 1;

	SCREEN_WIDTH  = 800; 
	SCREEN_HEIGHT = 600;

	if(!SetWeapon(weaponType))
		std::cout<<"Wrong weapon type \n";
	
	missle = new Missle*[bulletFireLimit];

	for(int i=0;i<bulletFireLimit;i++)
	{
		missle[i] = new Missle(directory,missleColider,(float)range,(float)speed);
		//std::cout<<" Missle["<<i<<"] Loaded \n"; //dla celow testowych
	}
	
	fired = false;
	active = false;
	//std::cout<<"Konstruktor weapon online! \n"; //dla celow testowych
}

Weapon::~Weapon(void)
{
	for ( int i = 0; i < bulletFireLimit; i++ )
		delete missle[i];
	delete[] missle;
}
void Weapon::UpdateCollision()
{
 	for(int i=0;i<bulletFireLimit;i++)
	{
		missle[i]->UpdateCollision();
	}
}
void Weapon::Logic(bool FiringLocked, sf::Vector2i target)
{	
				//FiringLocked - if weapon is firing constantly
	if( active == true )
	{

	if( FiringLocked && fired == true)
	{
		if( repetition.GetElapsedTime() > repeatRate )
		{
			repetition.Reset();
			destenation.x = target.x - (int)fireFromPosition.x;
			destenation.y = target.y - (int)fireFromPosition.y;
			distanceFromMouse=sqrt((float)(destenation.x)*(destenation.x)+(float)(destenation.y)*(destenation.y));
			
			if( missle[ReturnFirstAvailable(missle,bulletFireLimit)]->inMove == false )
			{
				missle[ReturnFirstAvailable(missle,bulletFireLimit)]->StartPosition(fireFromPosition);
				missle[ReturnFirstAvailable(missle,bulletFireLimit)]->SetTarget(destenation,distanceFromMouse);
				missle[ReturnFirstAvailable(missle,bulletFireLimit)]->inMove = true;
			}
		}
	
	}
	if( FiringLocked && fired == false)
	{
		if( repetition.GetElapsedTime() > repeatRate )
		{
		repetition.Reset();
		destenation.x = target.x - (int)fireFromPosition.x;
		destenation.y = target.y - (int)fireFromPosition.y;
		distanceFromMouse=sqrt((float)(destenation.x)*(destenation.x)+(float)(destenation.y)*(destenation.y));
		missle[0]->StartPosition(fireFromPosition);
		missle[0]->SetTarget(destenation,distanceFromMouse);
		missle[0]->inMove = true;
		fired = true;
		}
	}

	fired = false;
	active = false;
	}

	for(int i = 0;i<bulletFireLimit;i++)
	{	
		if(missle[i]->inMove == true)
		{
			missle[i]->Logic();
			active = true;
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
int Weapon::SetWeapon(WeaponType Weapon)
{
	switch(Weapon)
	{
	case Integral:
		directory = "Integral.png";
		damage = 10;
		range = 300;
		speed = 4.0;
		repeatRate = 0.5;
		bulletFireLimit = 5;
		error = 0.0;
		break;
	case Derivative:
		directory = "Derivative.png";
		damage = 1;
		range = 300;
		speed = 8.0;
		repeatRate = 0.2;
		bulletFireLimit = 5;
		error = 25.0;
		break;
	case Plus:
		directory = "Plus.png";
		damage = 50;
		range = 300;
		speed = 5.0;
		repeatRate = 0.25;
		bulletFireLimit = 5;
		error = 5.0;
		break;
	case Minus:
		directory = "Minus.png";
		damage = 5;
		range = 300;
		speed = 5.0;
		repeatRate = 0.25;
		bulletFireLimit = 5;
		error = 10.0;
		break;
	case YellowBall:
		directory = "YellowDeathBall.PNG";
		missleColider = "Hero";
		damage = 5;
		range = 300;
		speed = 5.0;
		repeatRate = 0.25;
		bulletFireLimit = 5;
		error = 10.0;
	default:
		return 0;
		break;
	}
	return 1;
}
