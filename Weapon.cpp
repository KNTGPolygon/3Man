#include "Weapon.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Functions.h"
Weapon::Weapon(std::string weaponName, int BulletFireLimit,float RepeatRate)
:bulletFireLimit(BulletFireLimit), repeatRate(RepeatRate)
{
	directory = "Integral.PNG";
	damage = 1;
	range = 1;
	speed = 1;

	SCREEN_WIDTH  = 800; 
	SCREEN_HEIGHT = 600;
	
	if(!Load(weaponName))
		std::cout<<"Loading weapon problem detected !\n";
	
	missle = new Missle*[bulletFireLimit];

	for(int i=0;i<bulletFireLimit;i++)
	{
		missle[i] = new Missle(directory,(float)range,(float)speed);
		//std::cout<<" Missle["<<i<<"] Loaded \n"; //dla celow testowych
	}
	
	fired = false;
	active = false;
	//std::cout<<"Konstruktor weapon online! \n"; //dla celow testowych
}

Weapon::~Weapon(void)
{
	delete[] missle;
}
void Weapon::Logic(bool FiringLocked, sf::Vector2i target)
{	
				//FiringLocked - if weapon is firing constantly
	if( active == true )
	{

	if(FiringLocked && fired == true)
	{
		if(repetition.GetElapsedTime()>repeatRate)
		{
			repetition.Reset();
			destenation.x = target.x - (int)fireFromPosition.x;
			destenation.y = target.y - (int)fireFromPosition.y;
			distanceFromMouse=sqrt((float)(destenation.x)*(destenation.x)+(float)(destenation.y)*(destenation.y));
			
			if(missle[ReturnFirstAvailable(missle,bulletFireLimit)]->inMove == false){
			missle[ReturnFirstAvailable(missle,bulletFireLimit)]->StartPosition(fireFromPosition);
			missle[ReturnFirstAvailable(missle,bulletFireLimit)]->SetTarget(destenation,distanceFromMouse);
			missle[ReturnFirstAvailable(missle,bulletFireLimit)]->inMove = true;
			}
		}
	
	}
		if(FiringLocked && fired == false)
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
bool Weapon::Load(std::string WeaponName)
{
	std::ifstream dataSet("Data/WeaponData.txt");
	std::string str;
	bool WeaponFound = false;
		 if (!dataSet) {
        std::cerr << "Nie uda³o siê za³adowaæ pliku " <<" WeaponData.txt "<< "\n";
		return 0;
				 }
		 if(dataSet.good() == true)
		 {
		  while( !dataSet.eof() )
			{		
				 dataSet >> str;
					if(str == WeaponName)
					{
					std::cout <<"weapon name : "<< str << "\n";
					WeaponFound = true;

						 dataSet >> str; 
						 if(dataSet.eof())break;
						 directory = str;
						 std::cout <<"directory : "<<str<<"\n";
						 
						 dataSet >> str;
						 if(dataSet.eof())break;
						 damage = atof(str.c_str());
						 std::cout <<"damage : "<<damage<<"\n";		

						 dataSet >> str;
						 if(dataSet.eof())break;
						 range = atof(str.c_str());
						 std::cout <<"range : "<<str<<"\n";

						 dataSet >> str;
						 if(dataSet.eof())break;
						 speed = atof(str.c_str());
						 std::cout <<"speed : "<<str<<"\n";

						 dataSet >> str;
						 if(dataSet.eof())break;
						 repeatRate = atof(str.c_str());
						 std::cout <<"reload : "<<str<<"\n";
						 
						  dataSet >> str;
						 if(dataSet.eof())break;
						 bulletFireLimit = atof(str.c_str());
						 std::cout <<"bulletLimit : "<<str<<"\n";

						 dataSet >> str;
						 if(dataSet.eof())break;
						 error = atof(str.c_str());
						 std::cout <<"error : "<<str<<"\n";
					}			   
			}
		  std::cout <<"#--------------------#\n";
			dataSet.close();
		 }
	return 1;
}