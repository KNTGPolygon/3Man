#include "GameEngine.h"
#include "Hero.h"
#include "Functions.h"
#include "ImageManager.h"
#include <iostream>
#include "Collision/BoxMask.h"
//-------------------------------- Hero
Hero::Hero(const sf::Input &_steering,float velocity)
	:steering(_steering),vel(velocity),weaponType(0) , numberOfWeapons(4)
{
	ANIMATION_TYPE = STAY;

	depth = 0;

	MyTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Player.PNG" );
	MyTexture.CreateMaskFromColor(sf::Color(255,0,255));
	MyTexture.SetSmooth(false);
	strMyPosition.SetScale(0.5,0.5);
	strMyPosition.SetPosition(0,0);

	Me.SetImage( MyTexture );
    Me.SetScale( 1, 1 ); 
	Me.SetSubRect(sf::IntRect(0,0,SPRITE_SIZE,SPRITE_SIZE));
	Me.SetPosition( 350, 425 );
	Me.SetCenter(18,25);
	Me.setType("hero");

	//Me.setBoxMask(sf::IntRect(0,26,SPRITE_SIZE,SPRITE_SIZE)); //ustawia maske kolizji na prostakat
	Me.setCircleMask(Me.GetCenter().x,Me.GetCenter().y,30);

	GameEngine::getInstance()->AddToCollisionList(&Me);

	animate = new Animate*[4];
	animate[0] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),3,15);   //DOWN
	animate[1] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,15,1); //LEFT
	animate[2] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,15,2); //RIGHT
	animate[3] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),3,15,3); //UP
	
	weapon = new Weapon*[numberOfWeapons];	
	weapon[0] = new Weapon("Plus");
	weapon[1] = new Weapon("Minus");
	weapon[2] = new Weapon("Derivative");
	weapon[3] = new Weapon("Integral");
	std::cout<<"Hero constructor online\n";
}

Hero::~Hero(void)
{
	for ( int i = 0; i < 4; i++ )
		delete animate[i];
	for ( int i = 0; i < numberOfWeapons; i++ )
		delete weapon[i];

	delete[] weapon;
	delete[] animate;

}

void Hero::Shoot()
{
}
void Hero::GetEvent()
{
		ANIMATION_TYPE = STAY;

		if( steering.IsKeyDown( sf::Key::A ) && myPosition.x>0 ){
		ANIMATION_TYPE = LEFT;
				Me.Move( -vel, 0 );
		}
		if( steering.IsKeyDown( sf::Key::D ) ){
		ANIMATION_TYPE = RIGHT;
				Me.Move( + vel, 0 );
		}
		if( steering.IsKeyDown( sf::Key::W )&& myPosition.y>0 ){
		ANIMATION_TYPE = UP;		
			    Me.Move( 0,- vel );
		}
		if( steering.IsKeyDown( sf::Key::S )){
		ANIMATION_TYPE = DOWN;
			    Me.Move( 0,+ vel );
		}
		
		if( steering.IsKeyDown(sf::Key::Num1) )weaponType=0;
		if( steering.IsKeyDown(sf::Key::Num2) )weaponType=1;
		if( steering.IsKeyDown(sf::Key::Num3) )weaponType=2;
		if( steering.IsKeyDown(sf::Key::Num4) )weaponType=3;

		weapon[weaponType]->active = true;

		for(int i = 0; i < 4 ; i++)
		{
		weapon[i]->SetFiringPosition(Me.GetPosition());
		weapon[i]->Logic(steering.IsMouseButtonDown(sf::Mouse::Left),
		sf::Vector2i(steering.GetMouseX()  - SCREEN_WIDTH/2 + (int)Me.GetPosition().x,
		steering.GetMouseY()  - SCREEN_HEIGHT/2 + (int)Me.GetPosition().y ));
		weapon[i]->active = false;
		}

}
void Hero::Display(sf::RenderWindow *window)
{
	strMyPosition.SetPosition(Me.GetPosition());
	strMyPosition.SetText("Sx = "+int2str((int)myPosition.x)+" Sy = "+int2str((int)myPosition.y));
	
	for(int i = 0 ; i < 4 ; i++)
	weapon[i]->Display( window );
	
	switch(ANIMATION_TYPE)
	{
		case STAY:
			window->Draw( Me );
			break;
		case RIGHT:
			animate[2]->Display( window );
			break;
		case LEFT:
			animate[1]->Display( window );
			break;		
		case UP:
			animate[3]->Display( window );
			break;
		case DOWN:
			animate[0]->Display( window );
			break;	
	}
	
	std::vector<SpriteExt*> list = GameEngine::getInstance()->getCollisionList();

	window->Draw( strMyPosition );

	if(GameEngine::getInstance()->devmode)
	{
		if ( GameEngine::getInstance()->DetectCollision(&Me) )
			((CircleMask*)Me.getCollisionMask())->Display(window,
													   sf::Vector2f(Me.GetPosition().x-Me.GetCenter().x,
																	Me.GetPosition().y-Me.GetCenter().y),
													   sf::Color(255, 0, 0));
		else
			((CircleMask*)Me.getCollisionMask())->Display(window,
													   sf::Vector2f(Me.GetPosition().x-Me.GetCenter().x,
																	Me.GetPosition().y-Me.GetCenter().y));
	}
}
void Hero::Move()
{

	box.Left = (int)myPosition.x;
	box.Top  = (int)myPosition.y;

	box.Bottom = SPRITE_SIZE   + box.Top;  
	box.Right  = SPRITE_SIZE   + box.Left;

}
void Hero::SetCamera(sf::View *View, sf::RenderWindow *window)
{
	View->SetHalfSize((float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT/2); 
	View->SetCenter(myPosition);
	window->SetView(*View);
}
void Hero::UpdatePosition()
{
	 GameEngine::getInstance()->AddToCollisionQuadtree(&Me);
	 myPosition     = Me.GetPosition();
	 for(int i = 0 ; i < 4 ; i++)
	 animate[i]->Update(Me.GetPosition());
	 depth = -Me.GetPosition().y;
}
sf::Vector2f Hero::GetPosition()
{
	return Me.GetPosition();
}
void Hero::PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	SCREEN_WIDTH  = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;

	for(int i = 0 ; i<numberOfWeapons ; i++)
	weapon[i]->PutScreenSize(_SCREEN_WIDTH, _SCREEN_HEIGHT );
}
