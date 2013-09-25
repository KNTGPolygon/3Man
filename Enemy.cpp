#include "Enemy.h"
#include "Hero.h"
#include "GameEngine.h"

Enemy::Enemy(sf::Vector2i Position,std::string fileName, bool RandomPathMode,
	float Velocity , float PullRange)
: velocity(Velocity),pullRange(PullRange), myPosition(Position)
{
	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+fileName );
	myTexture.SetSmooth( false );
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));

	mySprite.SetImage( myTexture );
	mySprite.SetPosition((float) myPosition.x ,(float) myPosition.y );
	mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
	mySprite.setType( "enemy" );
	startPosition = Position;
	target = Position;
	MovementVector.x = MovementVector.y = 150;

	
	if( RandomPathMode )
	{
	pathMode = RANDOM_PATHWALK;
		myAI = RANDOM_PATHWALK;
	}
	else
	{
	pathMode = PATHWALK;
	myAI = PATHWALK;
	}
	inMove		  = false;
	targetReached = false;
	attacking	  = false;
	pathNumber	  = 0;
	escapeRange = 300;
	pullRange = PullRange;
	waitTimeCounter = 0;
	waitTime = 50;

	path = new std::vector<sf::Vector2i> ;
	path->push_back(sf::Vector2i(500,500));
	path->push_back(sf::Vector2i(400,400));
	path->push_back(sf::Vector2i(100,100));
	path->push_back(sf::Vector2i(300,100));

	mySprite.setCircleMask(20,20,20);

	myWeapon = new Weapon(YellowBall);
	myWeapon->PutScreenSize(GameEngine::SCREEN_WIDTH,GameEngine::SCREEN_HEIGHT );
}

Enemy::~Enemy(void)
{
	delete myWeapon;
}
void Enemy::UpdateCollision()
{
 	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
	myWeapon->UpdateCollision();
}

void Enemy::UpdateSystem()
{
	UpdateCollision();
}

void Enemy::EventHandling()
{
	SetHeroPosition(Hero::myPosition);
	AI();
}

void Enemy::Logic(sf::Vector2i Target)
{
	if(GoToPosition( Target ) ){
		if ( GameEngine::getInstance()->DetectCollision( &mySprite, "wall" ) )
			mySprite.Move(-velocity*shiftVector);
		else
		mySprite.Move(velocity*shiftVector);

		myPosition.x =(int) mySprite.GetPosition().x;
		myPosition.y =(int) mySprite.GetPosition().y;

		targetReached = false;
	}
	else
		targetReached = true;
}
void Enemy::AI()
{
	switch( myAI )
	{
	case PATHWALK: //   ---  PATHWALK ---
	
	attacking = false;

		if( distanceFromHero < pullRange )
		{
			myAI = FOLLOW;
			std::cout<<"Following...\n"
				;
			break;
		}

		if(waitTimeCounter < waitTime && targetReached == true)
		{
			waitTimeCounter++;
			break;
		}
		else
		{
			waitTimeCounter = 0;
		}
		// satrt chodzenia sciezka
		if( pathNumber <  (signed) ( path->size() ) )
		{
			if (  targetReached == false )
			{
					Logic( path[0][pathNumber] );
					
			}else
			{
				targetReached = false;
				pathNumber++;
				std::cout<<"pathNumber = "<< pathNumber <<"\n";
			}
		}
		else
		if( pathNumber >= (signed)( path->size() - 1 ) )
		{
			pathNumber = 0;
			std::cout<<"pathNumber = "<< pathNumber <<"\n";
		}	
		// stop chodzenia sciezka
		break;
	case FOLLOW:	
			Logic( heroPosition );
			myAI = COMBAT;
			if( distanceFromHero > escapeRange )
			{
			myAI = pathMode;
			std::cout<<"Returning to path...\n";
			}

		break;
	case COMBAT:
		attacking = true;
		myWeapon->active = true;
		myWeapon->SetFiringPosition( sf::Vector2f( (float)myPosition.x, (float)myPosition.y) );
		myAI = FOLLOW;
		break;
	case RANDOM_PATHWALK: //   ---  RANDOM_PATHWALK ---
		myWeapon->active = false;
		if( distanceFromHero < pullRange )
		{
			myAI = FOLLOW;
			std::cout<<"Following...\n";
			break;
		}

		if(waitTimeCounter < waitTime && targetReached == true)
		{
			waitTimeCounter++;
			break;
		}
		else
		{
			waitTimeCounter = 0;
		}
		
		if (  targetReached == false )
		{
			Logic(target);
		}
		else
		{
		targetReached = false;
		GenerateRandomPath();
	//	std::cout<<"Going to point ( "<<target.x<<" , "<<target.y<<" )\n";
		}
		break;
	default:
		break;
	}

	myWeapon->Logic(attacking,heroPosition);
}

int Enemy::GoToPosition(sf::Vector2i Destination)
{
	distanceFromTarget = sqrt( pow((float)(myPosition.x - Destination.x),2) +  pow((float)(myPosition.y - Destination.y),2) );
	shiftVector.x = ( Destination.x - myPosition.x )/ distanceFromTarget ;
	shiftVector.y = ( Destination.y - myPosition.y )/ distanceFromTarget ;

	if( distanceFromTarget < 2.0 ) inMove = false;
	else inMove = true;

	return inMove;
}
void Enemy::RandomPathWalk()
{
		
		
}
void Enemy::GenerateRandomPath()
{
	target.x = rand()%( 2 * MovementVector.x ) + ( startPosition.x - MovementVector.x );
	target.y = rand()%( 2 * MovementVector.y ) + ( startPosition.y - MovementVector.y );
}
void Enemy::SetStartPosition(sf::Vector2f Position)
{
	mySprite.SetPosition( Position );
	myPosition.x = (int) Position.x;
	myPosition.y = (int) Position.y;
}
void Enemy::Display(sf::RenderWindow *window)
{
	window->Draw( mySprite );
	myWeapon->Display( window );

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
void Enemy::SetPathPoints(std::vector<sf::Vector2i> *Path)
{
	path = Path;
}
void Enemy::SetHeroPosition( sf::Vector2f HeroPosition )
{
	heroPosition.x = (int) HeroPosition.x;
	heroPosition.y = (int) HeroPosition.y;

	distanceFromHero = sqrt(pow(myPosition.x - HeroPosition.x,2) + pow(myPosition.y - HeroPosition.y,2));
}
