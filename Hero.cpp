#include "Hero.h"

//-------------------------------- Hero
Hero::Hero(sf::Input &_steering,float Velocity)
	:steering(_steering),Vel(Velocity)

{
	MyTexture.LoadFromFile( "Data/Textures/Player.png" );
	MyTexture.CreateMaskFromColor(sf::Color(255,0,255));

	strMyPosition.SetScale(0.5,0.5);
	strMyPosition.SetPosition(0,0);

	Me.SetImage( MyTexture );
    Me.SetScale( 1, 1 ); 
	Me.SetSubRect(sf::IntRect(0,0,42,42));
	Me.SetPosition( 350, 425 );
}

Hero::~Hero(void)
{
}
void Hero::GetPosition()
{
	 myPosition     = Me.GetPosition();
}
void Hero::GetEvent()
{
	
		if( steering.IsKeyDown( sf::Key::Left ) && myPosition.x>0 ){

				Me.Move( -Vel, 0 );
		}
		if( steering.IsKeyDown( sf::Key::Right ) ){

				Me.Move( + Vel, 0 );
		}
		if( steering.IsKeyDown( sf::Key::Up )&& myPosition.y>0 ){
				
			    Me.Move( 0,- Vel );
		}
		if( steering.IsKeyDown( sf::Key::Down )){
	
			    Me.Move( 0,+ Vel );
		}
		
}
void Hero::Display(sf::RenderWindow window)
{
	strMyPosition.SetPosition(Me.GetPosition());
	strMyPosition.SetText("Sx = "+int2str((int)myPosition.x)+" Sy = "+int2str((int)myPosition.y));
	
	window.Draw( Me );
	window.Draw( strMyPosition );
}
void Hero::Move()
{

	box.Left = (int)myPosition.x;
	box.Top  = (int)myPosition.y;

	box.Bottom = 42  + box.Top;  // 42 bo szerokosc tekstury
	box.Right  = 42   + box.Left;

}
void Hero::SetCamera()
{
	//View.SetCenter(myPosition);
}