#pragma once
#include <math.h>
#include <vector>
#include <iostream>

#include "Drawable.h" 
#include "Util.h"
#include "SpriteExt.h"
#include "ImageManager.h"
#include "Collision/BoxMask.h"
#include "Weapon.h"

class Enemy : public Drawable
{
public:
enum State{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	STAY,
	DEAD,
	COMBAT,
	FOLLOW,
	PATHWALK,
	RANDOM_PATHWALK,
	RETURN_TO_PATHWALK
	};
		bool pathSearched;
protected:
	
	bool gotHit;
	bool attacking;
	bool generated;

	int pathNumber;
	int waitTime;
	int waitTimeCounter;
	int iterator;
	int numberOfRandomPathPoints;
	int value;
	int frameCount;

	float velocity;
	float distanceFromTarget;
	float pullRange;
	float escapeRange;
	float distanceFromHero;

	std::vector<sf::Vector2i> *randomPatrolPath;
	std::vector<sf::Vector2i> pathfinderPath;

	State myAI;
	SpriteExt mySprite;
	sf::Image myTexture;
	sf::String exponent;

	sf::Vector2i myPosition;
	sf::Vector2i startPosition;
	sf::Vector2i target;
	sf::Vector2i heroPosition;
	sf::Vector2i MovementVector; //obszar generowania randomowej sciezki
	sf::Vector2f shiftVector;
	sf::Vector2i oldHeroPosition;

	int FindPath(sf::Vector2i Target);
	void Combat();
	void RandomPathWalk();
	void PathWalk();
	void Follow();
	void ReturnToPathWalk();
	void Colliding(bool minusCollision,bool plusCollision);
	void TypeSwichColliding();
	void SetImage(int Value);
	void SetImage(std::string filename);
	Weapon *myWeapon;
	
public:
	//pathFinding variables
	int myID;
	int pathStatus;

	sf::Shape sign;
	sf::Vector2i pathFinderPoint;

	bool targetReached;
	bool inMove;
	bool isMinus;
	bool isX;

	void Display(sf::RenderWindow *window);
	void UpdateSystem();
	void EventHandling();
	void Logic(sf::Vector2i Target);
	void UpdateCollision();
	int GoToPosition(sf::Vector2i Destination);
	
	void AI();
	void GenerateRandomPath();
	void SetStartPosition(sf::Vector2f Position);
	Enemy(sf::Vector2i Position = sf::Vector2i(300,300),int _value = 7, bool _isX = false,
		  std::string fileName = "Pirate.PNG" ,float Velocity = 1.0 , float PullRange = 250.0 );
	~Enemy(void);

	void SetHeroPosition( sf::Vector2f HeroPosition );
	void SetAIState( State _myAI );
	void SetPosition( sf::Vector2i newPostition );
	sf::Vector2i GetPosition();
	State GetAIState();
};
