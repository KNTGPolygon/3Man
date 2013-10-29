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
int Hero::currentWeapon;
bool Hero::armor;
bool Hero::invincible;

Hero::Hero(const sf::Input &_steering,float _velocity)
	: weaponType(0), numberOfWeapons(4), velocity(_velocity), steering(_steering)
{
	ANIMATION_TYPE = STAY;

	depth = 0;
	currentWeapon = weaponType;
	armor = false;
	invincible = false;
	invinc_timer.Reset();

	sf::Image& invinc_effect_img = ImageManager::getInstance()->loadImage("Data/Textures/Powerups/Invinc_effect.png");
	invinc_effect_img.SetSmooth(false);
	invinc_effect.SetImage(invinc_effect_img);
	invinc_effect.SetCenter(17,25);


	MyTexture = ImageManager::getInstance()->loadImage( "Data/Textures/hero_sheet.png" );
	MyTexture.CreateMaskFromColor(sf::Color(255,0,255));
	MyTexture.SetSmooth(false);
	strMyPosition.SetScale(0.5,0.5);
	strMyPosition.SetPosition(5,70);

	MyTexture_armor = ImageManager::getInstance()->loadImage( "Data/Textures/hero_sheet_armor.png" );
	MyTexture_armor.CreateMaskFromColor(sf::Color(255,0,255));
	MyTexture_armor.SetSmooth(false);

	Me.SetImage( MyTexture );
    Me.SetScale( 1, 1 ); 
	Me.SetSubRect(sf::IntRect(64,0,64+SPRITE_SIZE,SPRITE_SIZE));
	Me.SetPosition( 350, 425 );
	Me.SetCenter(16,25);
	Me.setType("Hero");
	Me.setBoxMask(sf::IntRect(0,26,SPRITE_SIZE,SPRITE_SIZE)); //ustawia maske kolizji na prostakat

	Me_armor.SetImage( MyTexture_armor );
    Me_armor.SetScale( 1, 1 );
	Me_armor.SetSubRect(sf::IntRect(64,0,64+SPRITE_SIZE,SPRITE_SIZE));
	Me_armor.SetPosition( 350, 425 );
	Me_armor.SetCenter(18,25);
	Me_armor.setType("Hero");
	Me_armor.setBoxMask(sf::IntRect(0,26,SPRITE_SIZE,SPRITE_SIZE)); //ustawia maske kolizji na prostakat

	animate = new Animate*[4];
	animate[0] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(2,0));   //DOWN
	animate[1] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(4,0)); //LEFT
	animate[2] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(6,0)); //RIGHT
	animate[3] = new Animate("Data/Textures/hero_sheet.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10); //UP

	animate_armor = new Animate*[4];
	animate_armor[0] = new Animate("Data/Textures/hero_sheet_armor.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(2,0));   //DOWN
	animate_armor[1] = new Animate("Data/Textures/hero_sheet_armor.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(4,0)); //LEFT
	animate_armor[2] = new Animate("Data/Textures/hero_sheet_armor.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10,sf::Vector2i(6,0)); //RIGHT
	animate_armor[3] = new Animate("Data/Textures/hero_sheet_armor.png",sf::Vector2i(SPRITE_SIZE,SPRITE_SIZE),Me.GetPosition(),2,10); //UP
	
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
	{
		delete animate[i];
		delete animate_armor[i];
	}
	for ( int i = 0; i < numberOfWeapons; i++ )
		delete weapon[i];

	delete[] weapon;
	delete[] animate;
	delete[] animate_armor;

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

		if (!GameState::death_effect)
			Me.Move( xstep, ystep );
		
		if ( GameEngine::getInstance()->DetectCollision(&Me, "wall") )
			Me.Move( -xstep, -ystep );

		if( steering.IsKeyDown(sf::Key::Num1) )weaponType=0;
		if( steering.IsKeyDown(sf::Key::Num2) )weaponType=1;
		if( steering.IsKeyDown(sf::Key::Num3) )weaponType=2;
		if( steering.IsKeyDown(sf::Key::Num4) )weaponType=3;

		currentWeapon = weaponType;
		weapon[weaponType]->active = true;
	
		for(int i = 0; i < 4 ; i++)
		{
		weapon[i]->SetFiringPosition(Me.GetPosition());
		weapon[i]->Logic( steering.IsMouseButtonDown(sf::Mouse::Left),
						  sf::Vector2i( (int)(GameEngine::getInstance()->GetMouseCoords().x), (int)(GameEngine::getInstance()->GetMouseCoords().y) ));
		weapon[i]->active = false;
		}

		if ( !invincible && (GameEngine::getInstance()->DetectCollision(&Me, "YellowDeathBall.PNG")))
		{
			if ( armor )
			{
				armor = false;
				SoundPlayer::getInstance()->Play(Snd::ArmorDestroy);
			}
			else if (!GameState::death_effect)
			{
				GameState::death_effect = true;
				GameState::death_anim_timer.Reset();
				GameState::restart_level = true;
				SoundPlayer::getInstance()->Play(Snd::HeroDeath);
			}
		}

}

void Hero::getHitByLaser()
{
	if ( armor )
			{
				armor = false;
				SoundPlayer::getInstance()->Play(Snd::ArmorDestroy);
			}
			else if (!GameState::death_effect && !invincible)
			{
				GameState::death_effect = true;
				GameState::death_anim_timer.Reset();
				GameState::restart_level = true;
				SoundPlayer::getInstance()->Play(Snd::HeroDeath);
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
			if (!armor) window->Draw( Me );
			else window->Draw( Me_armor );
			break;
		case RIGHT:
			if (!armor) animate[2]->Display( window );
			else animate_armor[2]->Display( window );
			break;
		case LEFT:
			if (!armor) animate[1]->Display( window );
			else animate_armor[1]->Display( window );
			break;		
		case UP:
			if (!armor) animate[3]->Display( window );
			else animate_armor[3]->Display( window );
			break;
		case DOWN:
			if (!armor) animate[0]->Display( window );
			else animate_armor[0]->Display( window );
			break;	
	}
		
	if ( invincible )
	{
		invinc_effect.SetPosition(myPosition);
		window->Draw(invinc_effect);
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
	 Me_armor.SetPosition(myPosition);
	 for(int i = 0 ; i < 4 ; i++)
	 {
		 animate[i]->Update(Me.GetPosition());
		 animate_armor[i]->Update(Me.GetPosition());
	 }
	 depth = (int)( -Me.GetPosition().y );
	 if ( GameEngine::getInstance()->DetectCollision(&Me, "armor") && !armor)
	 {
 		 armor = true;
		 SoundPlayer::getInstance()->Play(Snd::ArmorUpgrade);
	 }

	 	if ( GameEngine::getInstance()->DetectCollision(&Me, "invincibility") )
	 {
 		 invincible = true;
		 invinc_timer.Reset();
	 	 SoundPlayer::getInstance()->Play(Snd::ArmorUpgrade);
	 }

	 if ( invincible && invinc_timer.GetElapsedTime() >= 5 )
	 {
		 invincible = false;
	 }

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
