#include "Hero.h"
#include "Functions.h"
#include "ImageManager.h"
//-------------------------------- Hero
Hero::Hero(const sf::Input &_steering,float velocity)
	:steering(_steering),vel(velocity)
{
	//MyTexture.LoadFromFile( "Data/Textures/Player.png" );
	MyTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Player.PNG" );
	MyTexture.CreateMaskFromColor(sf::Color(255,0,255));

	strMyPosition.SetScale(0.5,0.5);
	strMyPosition.SetPosition(0,0);

	Me.SetImage( MyTexture );
    Me.SetScale( 1, 1 ); 
	Me.SetSubRect(sf::IntRect(0,0,SPRITE_SIZE,SPRITE_SIZE));
	Me.SetPosition( 350, 425 );

	weapon = new Weapon(steering);
}

Hero::~Hero(void)
{
}

void Hero::Shoot()
{
}
void Hero::GetEvent()
{
	
		if( steering.IsKeyDown( sf::Key::Left ) && myPosition.x>0 ){

				Me.Move( -vel, 0 );
		}
		if( steering.IsKeyDown( sf::Key::Right ) ){

				Me.Move( + vel, 0 );
		}
		if( steering.IsKeyDown( sf::Key::Up )&& myPosition.y>0 ){
				
			    Me.Move( 0,- vel );
		}
		if( steering.IsKeyDown( sf::Key::Down )){
	
			    Me.Move( 0,+ vel );
		}
		weapon->Logic();
		weapon->SetFiringPosition(Me.GetPosition());


}
void Hero::Display(sf::RenderWindow *window)
{
	strMyPosition.SetPosition(Me.GetPosition());
	strMyPosition.SetText("Sx = "+int2str((int)myPosition.x)+" Sy = "+int2str((int)myPosition.y));
	weapon->Display( window );
	window->Draw( Me );
	window->Draw( strMyPosition );
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
	 myPosition     = Me.GetPosition();
}
sf::Vector2f Hero::GetPosition()
{
	return Me.GetPosition();
}
void Hero::PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	SCREEN_WIDTH  = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;
	weapon->PutScreenSize(_SCREEN_WIDTH, _SCREEN_HEIGHT );
}