#include "Gui.h"
#include "../Hero.h"

Gui::Gui(int _screenWidth,int _screenHeight , sf::Vector2f start)
	: screenWidth(_screenWidth), screenHeight(_screenHeight)
{
	weaponChanged = true;
	numberOfWeapons = 4;
	sprite = new SpriteExt[numberOfWeapons];
	image  = new sf::Image[numberOfWeapons];
	image[0].LoadFromFile("Data/Textures/Weapons/Plus.PNG");
	image[0].SetSmooth(false);
	image[0].CreateMaskFromColor(sf::Color(255,0,255));
	sprite[0].SetImage( image[0] );
	sprite[0].SetPosition( start );
	image[1].LoadFromFile("Data/Textures/Weapons/Minus.PNG");
	image[1].SetSmooth(false);
	image[1].CreateMaskFromColor(sf::Color(255,0,255));
	sprite[1].SetImage( image[1] );
	sprite[1].SetPosition( start );
	image[2].LoadFromFile("Data/Textures/Weapons/Derivative.PNG");
	image[2].SetSmooth(false);
	image[2].CreateMaskFromColor(sf::Color(255,0,255));
	sprite[2].SetImage( image[2] );
	sprite[2].SetPosition( start );
	image[3].LoadFromFile("Data/Textures/Weapons/Integral.PNG");
	image[3].SetSmooth(false);
	image[3].CreateMaskFromColor(sf::Color(255,0,255));
	sprite[3].SetImage( image[3] );
	sprite[3].SetPosition( start );

	for(int i = 0 ; i < numberOfWeapons ; i++ )
	{
		sprite[i].SetCenter( sprite[i].GetSize().x /2 , sprite[i].GetSize().y /2 );
	}
}


Gui::~Gui(void)
{
}
void Gui::UpdateSystem()
{
	depth = -9999999;
	SetHeroPosition(  Hero::myPosition );
	SetCurrentWeapon( Hero::currentWeapon  );
	sf::Vector2f tempPos;
	if( weaponChanged )
	{
		
		for(int i = 0 ; i < numberOfWeapons ; i++ )
		{
			tempPos.x = heroPosition.x - screenWidth /2 + 550 + i*50;
			tempPos.y = heroPosition.y + screenHeight/2 - 90;
			sprite[i].SetPosition( tempPos );
			sprite[i].SetScale( 2.0 , 2.0 );
		}
		sprite[currentWeapon].SetScale(4.0,4.0);
	}else
	{
		for(int i = 0 ; i < numberOfWeapons ; i++ )
		{
			tempPos.x = heroPosition.x - screenWidth/2 +  550 + i*50;
			tempPos.y = heroPosition.y + screenHeight/2 - 90;
			sprite[i].SetPosition( tempPos );
		}
	}

}
void Gui::Display(sf::RenderWindow* window)
{
	for( int i = 0 ; i < numberOfWeapons ; i++ )
	window->Draw( sprite[i] );
}
void Gui::SetHeroPosition( sf::Vector2f _heroPosition )
{
	heroPosition = _heroPosition;
	sf::Vector2f tempPos;
}
void Gui::SetCurrentWeapon(int weapon)
{
	if( currentWeapon == weapon )
		weaponChanged = false;
	else 
		weaponChanged = true;
	currentWeapon = weapon;

}
