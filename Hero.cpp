#include "GameEngine.h"
#include "Hero.h"
#include "Util.h"
#include "ImageManager.h"
#include <iostream>
#include "Collision/BoxMask.h"
#include "Fx/EffectLayer.h"
#include "Sfx/SoundPlayer.h"
//-------------------------------- Hero

sf::Vector2f Hero::myPosition;

Hero::Hero(const sf::Input &_steering,float _velocity)
	: weaponType(0), numberOfWeapons(4), velocity(_velocity), steering(_steering)
{
	ANIMATION_TYPE = STAY;

	depth = 0;
	armor = false;
	invincible = false;

	MyTexture = ImageManager::getInstance()->loadImage( "Data/Textures/hero_sheet.png" );
	MyTexture.CreateMaskFromColor(sf::Color(255,0,255));
	MyTexture.SetSmooth(false);
	strMyPosition.SetScale(0.5,0.5);
	strMyPosition.SetPosition(5,70);

	Me.SetImage( MyTexture );
    Me.SetScale( 1, 1 ); 
	Me.SetSubRect(sf::IntRect(0,0,SPRITE_SIZE,SPRITE_SIZE));
	Me.SetPosition( 350, 425 );
	Me.SetCenter(18,25);
	Me.setType("Hero");

	Me.setBoxMask(sf::IntRect(0,26,SPRITE_SIZE,SPRITE_SIZE)); //ustawia maske kolizji na prostakat

	animate = new Animate*[4];
	animate[0] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(2,0));   //DOWN
	animate[1] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(4,0)); //LEFT
	animate[2] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(6,0)); //RIGHT
	animate[3] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10); //UP
	
	weapon = new Weapon*[numberOfWeapons];	
	weapon[0] = new Weapon(Plus);
	weapon[1] = new Weapon(Minus);
	weapon[2] = new Weapon(Derivative);
	weapon[3] = new Weapon(Integral);
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
void Hero::GetEvent()
{
		ANIMATION_TYPE = STAY;

		direction = 0;
		currentVelocity = 0;

		if( steering.IsKeyDown(keyUp) )
		{
			direction = 270;
			currentVelocity = velocity;
			ANIMATION_TYPE = UP;
		}
		if( steering.IsKeyDown(keyDown) )
		{
			direction = 90;
			currentVelocity = velocity;
			ANIMATION_TYPE = DOWN;
		}
		if( steering.IsKeyDown(keyLeft) )
		{
			direction = 180;
			currentVelocity = velocity;
			ANIMATION_TYPE = LEFT;
		}
		if( steering.IsKeyDown(keyRight) )
		{
			direction = 0;
			currentVelocity = velocity;
			ANIMATION_TYPE = RIGHT;
		}
		if( steering.IsKeyDown(keyUp) && steering.IsKeyDown(keyLeft) )
		{
			direction = 225;
			currentVelocity = velocity;
			ANIMATION_TYPE = UP;
		}
		if( steering.IsKeyDown(keyUp) && steering.IsKeyDown(keyRight) )
		{
			direction = 315;
			currentVelocity = velocity;
			ANIMATION_TYPE = UP;
		}
		if( steering.IsKeyDown(keyDown) && steering.IsKeyDown(keyLeft) )
		{
			direction = 135;
			currentVelocity = velocity;
			ANIMATION_TYPE = DOWN;
		}
		if( steering.IsKeyDown(keyDown) && steering.IsKeyDown(keyRight) )
		{
			direction = 45;
			currentVelocity = velocity;
			ANIMATION_TYPE = DOWN;
		}

		float xstep = Util::lengthdir_x( currentVelocity, direction );
		float ystep = Util::lengthdir_y( currentVelocity, direction );

		Me.Move( xstep, ystep );
		
		if ( GameEngine::getInstance()->DetectCollision(&Me, "wall") )
			Me.Move( -xstep, -ystep );

		if( steering.IsKeyDown(sf::Key::Num1) )weaponType=0;
		if( steering.IsKeyDown(sf::Key::Num2) )weaponType=1;
		if( steering.IsKeyDown(sf::Key::Num3) )weaponType=2;
		if( steering.IsKeyDown(sf::Key::Num4) )weaponType=3;

		weapon[weaponType]->active = true;

		for(int i = 0; i < 4 ; i++)
		{
		weapon[i]->SetFiringPosition(Me.GetPosition());
		weapon[i]->Logic( steering.IsMouseButtonDown(sf::Mouse::Left),
						  sf::Vector2i( (int)(GameEngine::getInstance()->GetMouseCoords().x), (int)(GameEngine::getInstance()->GetMouseCoords().y) ));
		weapon[i]->active = false;
		}

		/*if ( steering.IsKeyDown(sf::Key::Space) && !GameState::death_effect)
		{
			GameState::death_effect = true;
			GameState::death_anim_timer.Reset();
			GameState::restart_level = true;
		}*/

		if ( GameEngine::getInstance()->DetectCollision(&Me, "YellowDeathBall.PNG") && !GameState::death_effect )
		{
			GameState::death_effect = true;
			GameState::death_anim_timer.Reset();
			GameState::restart_level = true;
		}

}

void Hero::EventHandling()
{
	UpdatePosition();
	GetEvent();
}

void Hero::Display(sf::RenderWindow *window)
{
	strMyPosition.SetText( "Hero: " + Util::int2str((int)myPosition.x) + ", " + Util::int2str((int)myPosition.y) );

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
	
	GameEngine::getInstance()->SetDefaultView();
	window->Draw( strMyPosition );
	GameEngine::getInstance()->SetGameView();

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
	View->SetCenter(myPosition);
}
void Hero::UpdateCollision()
{
	GameEngine::getInstance()->AddToCollisionQuadtree(&Me);
	for(int i = 0; i < 4 ; i++)
	{
		weapon[i]->UpdateCollision();
	}
}

void Hero::UpdateSystem()
{
	UpdateCollision();
}

void Hero::UpdatePosition()
{
	 myPosition     = Me.GetPosition();
	 for(int i = 0 ; i < 4 ; i++)
	 animate[i]->Update(Me.GetPosition());
	 depth = (int)( -Me.GetPosition().y );
	 if ( GameEngine::getInstance()->DetectCollision(&Me, "armor") && !armor)
	 {
		 armor = true;
		 SoundPlayer::getInstance()->Play(Snd::ArmorUpgrade);
	 }
	 if ( GameEngine::getInstance()->DetectCollision(&Me, "invincibility") )
		 invincible = true;
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
