#include "Enemy.h"
#include "Hero.h"
#include "GameEngine.h"

Enemy::Enemy(sf::Vector2i Position, int _value, std::string fileName, 
	float Velocity , float PullRange)
: velocity(Velocity),pullRange(PullRange), myPosition(Position),value(_value)
{
	if( value == 10 )
	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+fileName );
	else if( value >= -9 && value <=9 )
	myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+Util::int2str( abs( value ) ) + ".PNG" );
	
	if( value < 0 )
		isMinus = true;
	else
		isMinus = false;

	sign = sf::Shape::Rectangle(0.0,0.0,10.0,4.0,sf::Color(0,0,0));
	sign.SetCenter(sign.GetPosition().x/2,sign.GetPosition().y/2);

	myTexture.SetSmooth( false );
	myTexture.CreateMaskFromColor(sf::Color(255,0,255));

	mySprite.SetImage( myTexture );
	mySprite.SetPosition((float) myPosition.x ,(float) myPosition.y );
	mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
	mySprite.setType( "enemy" );


	startPosition   = Position;
	pathFinderPoint = Position;
	target			= Position;

	MovementVector.x = MovementVector.y = 64;//150

	pathSearched = false;
	bool RandomPathMode = false;
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

	//myAI = STAY;

	inMove		  = false;
	targetReached = false;
	attacking	  = false;
	pathNumber	  = 0;
	escapeRange = 400;
	pullRange = PullRange;
	waitTimeCounter = 0;
	waitTime = 50;

	numberOfRandomPathPoints = 5;
	randomPatrolPath = new std::vector<sf::Vector2i>[numberOfRandomPathPoints] ;


	mySprite.setCircleMask(20,20,20);

	myWeapon = new Weapon(YellowBall);
	myWeapon->PutScreenSize(GameEngine::SCREEN_WIDTH,GameEngine::SCREEN_HEIGHT );

	myID = GameEngine::getInstance()->pathfinder->AddNewMobID();
	std::cout<<"enemy myID: " <<myID<<std::endl;
	generated = false;
}

Enemy::~Enemy(void)
{
	delete myWeapon;
}
void Enemy::UpdateCollision()
{
 	GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
	Colliding( GameEngine::getInstance()->DetectCollision(&mySprite,"Minus.PNG") 
			 , GameEngine::getInstance()->DetectCollision(&mySprite,"Plus.PNG" ) );
	myWeapon->UpdateCollision();
}

void Enemy::UpdateSystem()
{
	UpdateCollision();
}
void Enemy::Colliding(bool minusCollision,bool plusCollision)
{
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
void Enemy::EventHandling()
{
	SetHeroPosition(Hero::myPosition);
	AI();
}

void Enemy::Logic(sf::Vector2i Target)
{
	if( GoToPosition( Target ) ){

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
	if( generated == false )
	{
		GenerateRandomPath();
		generated = true;
	}
	attacking = false;
	switch( myAI )
	{
	case PATHWALK: //   ---  PATHWALK ---
	
	attacking = false;
	PathWalk();
		break;
	case FOLLOW:
		Follow();
		break;

	case COMBAT:
		//Logic( pathFinderPoint );
		attacking = true;
		myWeapon->active = true;
		myWeapon->SetFiringPosition( sf::Vector2f( (float)myPosition.x, (float)myPosition.y) );
		inMove = false;
		myAI = FOLLOW;
		break;

	case RANDOM_PATHWALK: //   ---  RANDOM_PATHWALK ---
		RandomPathWalk();
		break;
	case RETURN_TO_PATHWALK:
		ReturnToPathWalk();
		break;
	default:
		break;
	}

	myWeapon->Logic(attacking,heroPosition);
}
void Enemy::Follow()
{
	myAI = COMBAT;
	if( !pathSearched )
	{
		std::cout<<"mob"<<myID<<": Searching for path...\n";
		pathfinderPath.resize(0);
		iterator = 0;
		oldHeroPosition = sf::Vector2i( (int)Hero::myPosition.x,(int)Hero::myPosition.y );
		pathStatus = GameEngine::getInstance()->pathfinder->FindPath( myID, myPosition , oldHeroPosition );
		pathfinderPath = GameEngine::getInstance()->pathfinder->GetPath( myID );
		pathSearched = true;			
				
	}
	if( pathStatus == PathFinder::FOUND )
	{
		if( iterator != pathfinderPath.size() )
		{
			if( targetReached == true )
			{
				pathFinderPoint = pathfinderPath[iterator];
				pathFinderPoint.x = pathFinderPoint.x *32 + rand()%32;
				pathFinderPoint.y = pathFinderPoint.y *32 + rand()%32;
				iterator++;
				std::cout<<"mob"<<myID<<": heading to : x = "<<pathFinderPoint.x /32<<" y = " << pathFinderPoint.y/32<<std::endl;
				if( iterator % 5 == 0 )
				{
					if( (  oldHeroPosition.x/32 != (int)Hero::myPosition.x /32 ) && 
						( oldHeroPosition.y/32 != (int)Hero::myPosition.y /32 )  )
					{
						pathSearched = false;
					}
				}
			}
				
		}
		else
		{
			std::cout<<"mob"<<myID<<": target reached!"<<std::endl;
			myAI = RETURN_TO_PATHWALK;
			pathSearched = false;
		}
		Logic( pathFinderPoint );
	} else
	{
		myAI = RETURN_TO_PATHWALK;
		pathSearched = false;
		myWeapon->active = false;
		std::cout<<"No path found\n";
	}
	//Logic( pathFinderPoint );
	//pathFinderPoint
			

			
	if( distanceFromHero > escapeRange )
	{
		myAI = RETURN_TO_PATHWALK;
		pathSearched = false;
		std::cout<<"Returning to path...\n";
	}


}
void Enemy::RandomPathWalk()
{		
	
	myWeapon->active = false;
	if( distanceFromHero < pullRange )
	{
		myAI = FOLLOW;
		targetReached = true;
		//break;
		//std::cout<<"Following...\n";
	}else
	{
		if(waitTimeCounter < waitTime && targetReached == true)
		{
			waitTimeCounter++;
			//break;
		}
		else
		{
			waitTimeCounter = 0;
			
			if (  targetReached == false )
			{
				Logic(target);
			}
			else
			{
				targetReached = false;
				//GenerateRandomPath();

			//	std::cout<<"Going to point ( "<<target.x<<" , "<<target.y<<" )\n";
			}
		}
	}

}
void Enemy::PathWalk()
{
	if( distanceFromHero < pullRange )
	{
		myAI = FOLLOW;
		std::cout<<"Following...\n"	;
	}else
	{
		if(waitTimeCounter < waitTime && targetReached == true)
		{
			waitTimeCounter++;
		}
		else
		{
			waitTimeCounter = 0;			
			// start chodzenia sciezka
			if( iterator < randomPatrolPath[pathNumber].size() )
			{
				if( targetReached == true )
				{
					pathFinderPoint   = randomPatrolPath[pathNumber][iterator];//randomPatrolPath[pathNumber][iterator]
					pathFinderPoint.x = pathFinderPoint.x *32 + rand()%32;
					pathFinderPoint.y = pathFinderPoint.y *32 + rand()%32;
					iterator++;
				}
			}
			else
			{
				pathNumber++;
				iterator = 0;
				if( pathNumber >= numberOfRandomPathPoints )
					pathNumber = 0;
			}

			Logic( pathFinderPoint );
			// stop chodzenia sciezka
		}
	}
}
void Enemy::ReturnToPathWalk()
{
	if( FindPath( target ) == PathFinder::FOUND )
	{
		if( iterator != pathfinderPath.size() )
		{
			if( targetReached == true )
			{
				pathFinderPoint = pathfinderPath[iterator];
				pathFinderPoint.x = pathFinderPoint.x *32 + rand()%32;
				pathFinderPoint.y = pathFinderPoint.y *32 + rand()%32;
				iterator++;
			}
				
		}
		else
		{
			myAI = pathMode;
			pathSearched = false;
		}
		Logic( pathFinderPoint );
	}
}
Enemy::State Enemy::GetAIState()
{
	return myAI;
}
void Enemy::SetAIState( State _myAI )
{
	myAI = _myAI;
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

int Enemy::FindPath(sf::Vector2i Target)
{
	if( !pathSearched )
	{
		pathfinderPath.resize(0);
		iterator = 0;
		pathStatus = GameEngine::getInstance()->pathfinder->FindPath( myID, myPosition , Target );
		pathfinderPath = GameEngine::getInstance()->pathfinder->GetPath( myID );
		pathSearched = true;			
				
	}
	return pathStatus;
}

void Enemy::GenerateRandomPath()
{
	std::cout<<"ID: " <<myID<<std::endl;

	std::cout<<"start : "<<startPosition.x<<" "<<startPosition.y<<std::endl;
	for( int i = 0 ; i < numberOfRandomPathPoints ; i++ )
	{
		do{
		target.x = rand()%( 2 * MovementVector.x ) + ( startPosition.x - MovementVector.x );
		target.y = rand()%( 2 * MovementVector.y ) + ( startPosition.y - MovementVector.y );
		std::cout<<target.x<<" "<<target.y<<"\n";
		pathSearched = false;
		if( FindPath( target ) == PathFinder::FOUND )
		{
			pathStatus = PathFinder::NONEXISTENT;
			randomPatrolPath[i] = pathfinderPath;
			break;
		}

		}while( pathStatus != PathFinder::FOUND );
	}
		
		
}

void Enemy::Display(sf::RenderWindow *window)
{
	window->Draw( mySprite );
	myWeapon->Display( window );

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
void Enemy::SetStartPosition(sf::Vector2f Position)
{
	mySprite.SetPosition( Position );
	myPosition.x = (int) Position.x;
	myPosition.y = (int) Position.y;
}
void Enemy::SetPosition( sf::Vector2i newPosition )
{
	mySprite.SetPosition( (float)newPosition.x,(float)newPosition.y );
}
sf::Vector2i Enemy::GetPosition()
{
	return sf::Vector2i( (int)myPosition.x , (int)myPosition.y );
}
void Enemy::SetImage(int Value)
{
			myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+Util::int2str( abs( Value ) ) + ".PNG" );
			myTexture.SetSmooth( false );
			myTexture.CreateMaskFromColor(sf::Color(255,0,255));

			mySprite.SetImage( myTexture );
			mySprite.SetPosition((float) myPosition.x ,(float) myPosition.y );
			mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
}

void Enemy::SetHeroPosition( sf::Vector2f HeroPosition )
{
	heroPosition.x = (int) HeroPosition.x;
	heroPosition.y = (int) HeroPosition.y;

	distanceFromHero = sqrt(pow(myPosition.x - HeroPosition.x,2) + pow(myPosition.y - HeroPosition.y,2));
}
