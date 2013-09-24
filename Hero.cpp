#include "GameEngine.h"
#include "Hero.h"
#include "Util.h"
#include "ImageManager.h"
#include <iostream>
#include "Collision/BoxMask.h"
//-------------------------------- Hero
Hero::Hero(const sf::Input &_steering,float velocity)
	:steering(_steering),vel(velocity),weaponType(0) , numberOfWeapons(4)
{
	ANIMATION_TYPE = STAY;

	speed = 2;
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

	Me.setBoxMask(sf::IntRect(0,26,SPRITE_SIZE,SPRITE_SIZE)); //ustawia maske kolizji na prostakat

	animate = new Animate*[4];
	animate[0] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),3,15);   //DOWN
	animate[1] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,15,1); //LEFT
	animate[2] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,15,2); //RIGHT
	animate[3] = new Animate("Data/Textures/Player.PNG",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),3,15,3); //UP
	
	weapon = new Weapon*[numberOfWeapons];	
	weapon[0] = new Weapon("Plus",Plus);
	weapon[1] = new Weapon("Minus",Minus);
	weapon[2] = new Weapon("Derivative",Derivative);
	weapon[3] = new Weapon("Integral",Integral);
	std::cout<<"Hero constructor online\n";

	keyUp = sf::Key::W;
	keyDown = sf::Key::S;
	keyLeft = sf::Key::A;
	keyRight = sf::Key::D;

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
void Hero::GetEvent(int mapPixelatedSize)
{
		ANIMATION_TYPE = STAY;

		int dir = 0;
		int sp = 0;

		if( steering.IsKeyDown(keyUp) )
		{
			dir = 270;
			sp = speed;
			ANIMATION_TYPE = UP;
		}
		if( steering.IsKeyDown(keyDown) )
		{
			dir = 90;
			sp = speed;
			ANIMATION_TYPE = DOWN;
		}
		if( steering.IsKeyDown(keyLeft) )
		{
			dir = 180;
			sp = speed;
			ANIMATION_TYPE = LEFT;
		}
		if( steering.IsKeyDown(keyRight) )
		{
			dir = 0;
			sp = speed;
			ANIMATION_TYPE = RIGHT;
		}
		if( steering.IsKeyDown(keyUp) && steering.IsKeyDown(keyLeft) )
		{
			dir = 225;
			sp = speed;
			ANIMATION_TYPE = UP;
		}
		if( steering.IsKeyDown(keyUp) && steering.IsKeyDown(keyRight) )
		{
			dir = 315;
			sp = speed;
			ANIMATION_TYPE = UP;
		}
		if( steering.IsKeyDown(keyDown) && steering.IsKeyDown(keyLeft) )
		{
			dir = 135;
			sp = speed;
			ANIMATION_TYPE = DOWN;
		}
		if( steering.IsKeyDown(keyDown) && steering.IsKeyDown(keyRight) )
		{
			dir = 45;
			sp = speed;
			ANIMATION_TYPE = DOWN;
		}

		Me.Move( Util::lengthdir_x(sp, dir), Util::lengthdir_y(sp, dir) );
		
		if( steering.IsKeyDown(sf::Key::Num1) )weaponType=0;
		if( steering.IsKeyDown(sf::Key::Num2) )weaponType=1;
		if( steering.IsKeyDown(sf::Key::Num3) )weaponType=2;
		if( steering.IsKeyDown(sf::Key::Num4) )weaponType=3;

		weapon[weaponType]->active = true;

		sf::Vector2f mouse_coords = GameEngine::getInstance()->getWindow().ConvertCoords( steering.GetMouseX(),
																						  steering.GetMouseY(),
																						  &GameEngine::getInstance()->getView() );
		for(int i = 0; i < 4 ; i++)
		{
		weapon[i]->SetFiringPosition(Me.GetPosition());
		weapon[i]->Logic(steering.IsMouseButtonDown(sf::Mouse::Left), sf::Vector2i( (int)mouse_coords.x, (int)mouse_coords.y ));
		weapon[i]->active = false;
		}

}
void Hero::Display(sf::RenderWindow *window)
{
	strMyPosition.SetPosition(Me.GetPosition());
	strMyPosition.SetText("Sx = "+Util::int2str((int)myPosition.x)+" Sy = "+Util::int2str((int)myPosition.y));
	
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
	
	window->Draw( strMyPosition );

	if(GameEngine::getInstance()->devmode)
	{
		if ( GameEngine::getInstance()->DetectCollision(&Me) )
			((BoxMask*)Me.getCollisionMask())->Display(window,
													   sf::Vector2f(Me.GetPosition().x-Me.GetCenter().x,
																	Me.GetPosition().y-Me.GetCenter().y),
													   sf::Color(255, 0, 0));
		else
			((BoxMask*)Me.getCollisionMask())->Display(window,
													   sf::Vector2f(Me.GetPosition().x-Me.GetCenter().x,
																	Me.GetPosition().y-Me.GetCenter().y));
	}
	
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
