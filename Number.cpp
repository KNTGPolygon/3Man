#include "Number.h"
#include "GameEngine.h"
#include <math.h>
Number::Number(sf::Vector2i Position,int Value, bool RandomPathMode
			   ,float Velocity , float PullRange) 
:value( Value )
{
	pullRange = PullRange;
	isMinus = false;
	if( !( value >= -9 && value <= 9 ) )
		value = 0;
	else
		if( value < 0 )
	{
		isMinus = true;
		sign = sf::Shape::Rectangle(0.0,0.0,10.0,4.0,sf::Color(0,0,0));
		sign.SetCenter(sign.GetPosition().x/2,sign.GetPosition().y/2);
	}

	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+Util::int2str( abs( value ) ) + ".PNG" );
	myTexture.SetSmooth( false );
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));

	mySprite.SetImage( myTexture );
	mySprite.SetPosition((float) Position.x ,(float) Position.y );
	mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
	mySprite.setType( "enemy" );
	
	startPosition   = Position;
	pathFinderPoint = Position;
	target			= Position;
	MovementVector.x = MovementVector.y = 64;

	pathSearched = false;
	RandomPathMode = false;

	if( RandomPathMode )
	{
		myAI = RANDOM_PATHWALK;
	pathMode = RANDOM_PATHWALK;
	}
	else
	{
		myAI = PATHWALK;
	pathMode = PATHWALK;
	}

	inMove		  = false;
	targetReached = false;
	attacking	  = false;
	pathNumber	  = 0;
	escapeRange = 300;
	pullRange = PullRange;
	waitTimeCounter = 0;
	waitTime = 50;


	numberOfRandomPathPoints = 5;
	randomPatrolPath = new std::vector<sf::Vector2i>[numberOfRandomPathPoints] ;

	mySprite.setCircleMask(20,20,20);

	myWeapon = new Weapon(YellowBall);
	myWeapon->PutScreenSize(GameEngine::SCREEN_WIDTH,GameEngine::SCREEN_HEIGHT );

	//myID = GameEngine::getInstance()->pathfinder->AddNewMobID();
	std::cout<<"number myID: " <<myID<<std::endl;
	generated = false;
}

Number::~Number(void)
{
}
void Number::SetImage(int Value)
{
			myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+Util::int2str( abs( Value ) ) + ".PNG" );
			myTexture.SetSmooth( false );
			myTexture.CreateMaskFromColor(sf::Color(255,0,255));

			mySprite.SetImage( myTexture );
			mySprite.SetPosition((float) myPosition.x ,(float) myPosition.y );
			mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
}
void Number::UpdateCollision()
{
 	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
	Colliding( GameEngine::getInstance()->DetectCollision(&mySprite,"Minus.PNG") 
			 , GameEngine::getInstance()->DetectCollision(&mySprite,"Plus.PNG" ) );
	myWeapon->UpdateCollision();
}
void Number::UpdateSystem()
{
	UpdateCollision();
}
void Number::Colliding(bool minusCollision,bool plusCollision)
{
	//DetectCollision(SpriteExt*, std::string);
	if(minusCollision)
	{
		if( value > 0 && value < 9)
		{
			value--;
			isMinus = false;
			SetImage(value);
		}
		else
			if( value >-9 )
			{
			value--;
			isMinus = true;
				if ( value == 0 ) isMinus = false;		
			SetImage(value);
			}
	}
	else if(plusCollision)
	{
		if( value > 0 && value < 9)
		{
			value++;
			isMinus = false;
			SetImage(value);
		}
		else
		if( value <= 0 && value >= -9 )
		{
			value++;
			isMinus = true;
			if ( value == 0 ) isMinus = false;		
			SetImage(value);
		}
	}
}
void Number::Display(sf::RenderWindow *window)
{
	depth = (int)( -mySprite.GetPosition().y );
	window->Draw( mySprite );
	if ( isMinus )
	{
		sign.SetPosition( mySprite.GetPosition().x - 20,mySprite.GetPosition().y);	
		window->Draw( sign );
	}
	if(GameEngine::getInstance()->devmode)
	{
		if ( GameEngine::getInstance()->DetectCollision(&mySprite) )
		((CircleMask*)mySprite.getCollisionMask())->Display(window,
														 sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x,
																	  mySprite.GetPosition().y-mySprite.GetCenter().y), sf::Color(255,0,0));
		else
		((CircleMask*)mySprite.getCollisionMask())->Display(window,
														 sf::Vector2f(mySprite.GetPosition().x-mySprite.GetCenter().x,
																	  mySprite.GetPosition().y-mySprite.GetCenter().y));
	}

}