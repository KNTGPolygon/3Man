#include "Enemy.h"

Enemy::Enemy(sf::Vector2i Position,std::string fileName, float Velocity,
	float PullRange)
:myPosition(Position) ,velocity(Velocity),pullRange(PullRange)
{
	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+fileName );
	myTexture.SetSmooth( false );
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));

	mySprite.SetImage( myTexture );
	mySprite.SetPosition((float) myPosition.x ,(float) myPosition.y );
	
	myAI = PATHWALK;

	inMove		  = false;
	targetReached = false;
	pathNumber	  = 0;
	escapeRange = 300;
	pullRange = PullRange;

	path = new std::vector<sf::Vector2i> ;
	path->push_back(sf::Vector2i(500,500));
	path->push_back(sf::Vector2i(400,400));
	path->push_back(sf::Vector2i(100,100));
	path->push_back(sf::Vector2i(300,100));
}

Enemy::~Enemy(void)
{
}
void Enemy::Logic(sf::Vector2i Target)
{
	if(GoToPosition( Target ) ){
		switch ( myDirection )
		{
	/*	case UP:
			mySprite.Move( 0 , -velocity );
				  break;
		case DOWN:
			mySprite.Move( 0 , velocity  );
				  break;
		case RIGHT:
			mySprite.Move( velocity , 0  );
				  break;
		case LEFT:
			mySprite.Move( -velocity , 0 );
				  break; */
		case STAY:
				  break; 
		default:
			mySprite.Move(velocity*shiftVector);
			break;
		
		}
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
	case PATHWALK:

		if( distanceFromHero < pullRange )
		{
			myAI = FOLLOW;
			std::cout<<"Following...\n";
			break;
		}

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
				//system("pause");
			}
		}
		else
		if( pathNumber >= (signed)( path->size() - 1 ) )
		{
			pathNumber = 0;
			std::cout<<"pathNumber = "<< pathNumber <<"\n";
		}		
		break;
	case FOLLOW:	
			Logic( heroPosition );
			if( distanceFromHero > escapeRange )
			{
			myAI = PATHWALK;
			std::cout<<"Returning to path...\n";
			}

		break;
	case COMBAT:
		break;
	default:
		break;
	}
}

int Enemy::GoToPosition(sf::Vector2i Destination)
{
	distanceFromTarget = sqrt( pow((float)(myPosition.x - Destination.x),2) +  pow((float)(myPosition.y - Destination.y),2) );
	shiftVector.x = ( Destination.x - myPosition.x )/ distanceFromTarget ;
	shiftVector.y = ( Destination.y - myPosition.y )/ distanceFromTarget ;

	if( distanceFromTarget < 5.0 ) inMove = false;
	else inMove = true;

	/*if(Destination.x <= myPosition.x && Destination.y < myPosition.y )		//I
		myDirection = LEFT;
	else if(Destination.x > myPosition.x && Destination.y <= myPosition.y )	//II
		myDirection = UP;
	else if(Destination.x < myPosition.x && Destination.y >= myPosition.y )	//III
		myDirection = DOWN;
	else if(Destination.x >= myPosition.x && Destination.y > myPosition.y )	//IV
		myDirection = RIGHT;
		*/
	if(Destination == myPosition)
		myDirection = STAY;

	return inMove;
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