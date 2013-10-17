#include "Enemy.h"
#include "Hero.h"
#include "GameEngine.h"
#include "Sfx/SoundPlayer.h"

Enemy::Enemy(sf::Vector2i Position, int _value, bool _isX, std::string fileName,
	float Velocity , float PullRange)
: velocity(Velocity),pullRange(PullRange), myPosition(Position),value(_value),isX(_isX)
{
	isX    = false;
	if( value == 10 )
	SetImage( fileName );
	else if( value >= -9 && value <=9 )
	SetImage( Util::int2str( abs( value ) ) + ".PNG" );
	else
	{
		value = -9 + rand()%19;
		if( value == 0 ) value = 1;
		isX = true;
		SetImage( "x.PNG" );
	}


	exponent.SetText( Util::int2str( value ) );
	exponent.SetSize( 25.0 );
	exponent.SetPosition( sf::Vector2f( (float) Position.x, (float) Position.y ) );
	exponent.SetColor( sf::Color( 0,0,0) );

	if( value < 0 )
		isMinus = true;
	else
		isMinus = false;

	sign = sf::Shape::Rectangle(0.0,0.0,10.0,4.0,sf::Color(0,0,0));
	sign.SetCenter(sign.GetPosition().x/2,sign.GetPosition().y/2);

	mySprite.setType( "enemy" );

	startPosition   = Position;
	pathFinderPoint = Position;
	target			= Position;

	MovementVector.x = MovementVector.y = 64;//150
	frameCount = 0;
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
	if( myAI != DEAD )
	{
 		GameEngine::getInstance()->AddToCollisionQuadtree(&mySprite);
		if( isX )
		Colliding( GameEngine::getInstance()->DetectCollision(&mySprite,"Derivative.PNG") 
				 , GameEngine::getInstance()->DetectCollision(&mySprite,"Integral.PNG" ) );
		else
		Colliding( GameEngine::getInstance()->DetectCollision(&mySprite,"Minus.PNG") 
				 , GameEngine::getInstance()->DetectCollision(&mySprite,"Plus.PNG" ) );
		TypeSwichColliding();
	}
	myWeapon->UpdateCollision();
	
}

void Enemy::UpdateSystem()
{
	UpdateCollision();
	frameCount++;
	if(frameCount >= 100)
		frameCount = 0;

}
void Enemy::Colliding(bool minusCollision,bool plusCollision)
{
	if(minusCollision)
	{
		if( value > 0 && value <= 9)
		{
			value--;
			isMinus = false;
			if ( value == 0 )
				if(!isX)
				{
					myAI = DEAD;
					SoundPlayer::getInstance()->Play(Snd::EnemyDeath);
				}

			SetImage(value);
		}
		else
			if( value >-9 )
			{
				value--;
				isMinus = true;
				if ( value == 0 )
				{
					isMinus = false;
					if(!isX)
					{
						myAI = DEAD;
						SoundPlayer::getInstance()->Play(Snd::EnemyDeath);
					}
					isX     = false;
				}
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
			if ( value == 0 )
			{
				isMinus = false;
				if(!isX)
				{
					myAI = DEAD;
					SoundPlayer::getInstance()->Play(Snd::EnemyDeath);
				}
				isX		= false;
			}
			SetImage(value);
		}
	}
}
void Enemy::TypeSwichColliding()
{
	if( !isX )
	{
		if( GameEngine::getInstance()->DetectCollision(&mySprite,"Derivative.PNG") )
		{
			value = 0;
			isMinus = false;
			SetImage( value );
			myAI = DEAD;
		}else
		if( GameEngine::getInstance()->DetectCollision(&mySprite,"Integral.PNG" ) )
		{
			value = 1;
			isX = true;
			SetImage( "x.PNG" );
			exponent.SetText( Util::int2str( value ) );
		}
	}else
	{
		if( value == 0 )
		{
			isX = false;
			value = 1;
			SetImage( value );
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
	PathWalk();
		break;
	case FOLLOW:
		Follow();
		break;

	case COMBAT:
		Combat();
		break;
	case RANDOM_PATHWALK:
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
void Enemy::Combat()
{
		Logic( pathFinderPoint );
		attacking = true;
		myWeapon->active = true;
		myWeapon->SetFiringPosition( sf::Vector2f( (float)myPosition.x, (float)myPosition.y) );
		inMove = false;
		myAI = FOLLOW;
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
				pathFinderPoint.x = pathFinderPoint.x *32 +8 + rand()%24;
				pathFinderPoint.y = pathFinderPoint.y *32 +8 + rand()%24;
				iterator++;
				std::cout<<"mob"<<myID<<": heading to : x = "<<pathFinderPoint.x /32<<" y = " << pathFinderPoint.y/32<<std::endl;
				if( iterator % 5 == 0 )
				{
					if( (  oldHeroPosition.x/32 != (int)Hero::myPosition.x /32 ) && 
						(  oldHeroPosition.y/32 != (int)Hero::myPosition.y /32 )  )
					{
						pathSearched = false;
					}
				}
			}
				
		}
		else
		{
			std::cout<<"mob"<<myID<<": target reached!"<<std::endl;
			myAI = FOLLOW;
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
	attacking = false;
	if( frameCount == 50 )
	{
		if( distanceFromHero < pullRange )
		{
			if( GameEngine::getInstance()->pathfinder->IsInSight(myPosition,heroPosition) )
			{
				myAI = FOLLOW;
				std::cout<<"Following...\n"	;
			}
		}
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
					pathFinderPoint.x = pathFinderPoint.x *32 +8 + rand()%24;
					pathFinderPoint.y = pathFinderPoint.y *32 +8 + rand()%24;
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
	if( frameCount == 50 )
	{
		if( distanceFromHero < pullRange )
		{
			if( GameEngine::getInstance()->pathfinder->IsInSight(myPosition,heroPosition) )
			{
				myAI = FOLLOW;
				std::cout<<"Following...\n"	;
			}
		}
	}else
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
		if( pathStatus == PathFinder::FOUND )
		{
		pathfinderPath = GameEngine::getInstance()->pathfinder->GetPath( myID );
		pathSearched = true;	
		}
				
	}
	return pathStatus;
}

void Enemy::GenerateRandomPath()
{
	std::cout<<"ID: " <<myID<<std::endl;

	//std::cout<<"start : "<<startPosition.x<<" "<<startPosition.y<<std::endl;

	pathStatus = PathFinder::NONEXISTENT;
	for( int i = 0 ; i < numberOfRandomPathPoints ; i++ )
	{
		do{
		target.x = rand()%( 2 * MovementVector.x ) + ( startPosition.x - MovementVector.x );
		target.y = rand()%( 2 * MovementVector.y ) + ( startPosition.y - MovementVector.y );
	//	std::cout<<target.x<<" "<<target.y<<"\n";
		pathSearched = false;
		if( (target.x/32 != myPosition.x/32) &&
		    (target.y/32 != myPosition.y/32) )
		{
			if( FindPath( target ) == PathFinder::FOUND )
			{
				pathStatus = PathFinder::NONEXISTENT;
				randomPatrolPath[i] = pathfinderPath;
				break;
			}
		}
		}while( pathStatus != PathFinder::FOUND );
	}
		
		
}

void Enemy::Display(sf::RenderWindow *window)
{
	if( myAI != DEAD )
	{
		window->Draw( mySprite );
		if ( isMinus && !isX)
		{
			sign.SetPosition( mySprite.GetPosition().x - 20,mySprite.GetPosition().y);	
			window->Draw( sign );
		}
		if ( isX )
		{
			if( value >= 0 )
			exponent.SetPosition( mySprite.GetPosition().x + 20.0, mySprite.GetPosition().y - 40.0 );
			else
			exponent.SetPosition( mySprite.GetPosition().x + 10.0, mySprite.GetPosition().y - 40.0 );

			window->Draw( exponent );
		}
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
		myWeapon->Display( window );
}
void Enemy::SetStartPosition(sf::Vector2f Position)
{
	mySprite.SetPosition( Position );
	myPosition.x = (int) Position.x;
	myPosition.y = (int) Position.y;
	if( isX )
	{
		exponent.SetPosition( Position.x + 5.0, Position.y + 5.0 );
	}
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
	if( !isX )
	{
			myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+Util::int2str( abs( Value ) ) + ".PNG" );
			myTexture.SetSmooth( false );
			myTexture.CreateMaskFromColor(sf::Color(255,0,255));

			mySprite.SetImage( myTexture );
			mySprite.SetPosition((float) myPosition.x ,(float) myPosition.y );
			mySprite.SetCenter(mySprite.GetSize().x/2,mySprite.GetSize().y/2);
	}else
	{
		exponent.SetText( Util::int2str( Value ) );
	}
}
void Enemy::SetImage(std::string filename)
{
			myTexture = ImageManager::getInstance()->loadImage( "Data/Textures/Enemy/"+filename );
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
