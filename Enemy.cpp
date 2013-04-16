#include "Enemy.h"

Enemy::Enemy(sf::Vector2i Position,std::string fileName, float Velocity )
:myPosition(Position) ,velocity(Velocity)
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
		case UP:
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
				  break;
		case STAY:
				  break;
		default:
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
		if( pathNumber <  (signed) ( path->size() ) )
		{
			if (  targetReached == false )
			{
					Logic( path[0][pathNumber] );
					
					/*
					std::cout<<" unsigned path size = "<< path->size()<<"\n";
					std::cout<<" signed path size = "<<(signed) path->size()<<"\n";
					std::cout<<" path[2].x  = "<< path[2]->x <<"\n";
					std::cout<<" path[2].y  = "<< path[2]->y <<"\n";
					std::cout<<" path[0][0].x  = "<< path[0][0].x <<"\n";
					std::cout<<" path[0][0].y  = "<< path[0][0].y <<"\n";
					std::cout<<" path[0][1].x  = "<< path[0][1].x <<"\n";
					std::cout<<" path[0][1].y  = "<< path[0][1].y <<"\n";
					system("pause");
					system("pause");
					*/
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
			//system("pause");
		}		
		break;
	case FOLLOW:
		break;
	case COMBAT:
		break;
	default:
		break;
	}
	/*if(targetReached == false )
	{
		
	}
	else
	
	Logic( target );
	*/
}

int Enemy::GoToPosition(sf::Vector2i Destination)
{
	distanceFromTarget = sqrt( pow((float)(myPosition.x - Destination.x),2) +  pow((float)(myPosition.y - Destination.y),2) );
	
	if( distanceFromTarget < 5.0 ) inMove = false;
	else inMove = true;

	if(Destination.x <= myPosition.x && Destination.y < myPosition.y )		//I
		myDirection = LEFT;
	else if(Destination.x > myPosition.x && Destination.y <= myPosition.y )	//II
		myDirection = UP;
	else if(Destination.x < myPosition.x && Destination.y >= myPosition.y )	//III
		myDirection = DOWN;
	else if(Destination.x >= myPosition.x && Destination.y > myPosition.y )	//IV
		myDirection = RIGHT;
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