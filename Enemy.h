#pragma once
#include "Drawable.h" 
#include "SpriteExt.h"
#include "ImageManager.h"
#include "Collision/BoxMask.h"
#include <math.h>
#include <vector>
#include <iostream>
class Enemy : public Drawable
{
private:
	bool inMove;
	bool targetReached;

	int pathNumber;

	float velocity;
	float distanceFromTarget;

	float pullRange;
	float escapeRange;
	float distanceFromHero;

	std::vector<sf::Vector2i> *path;
private:

	enum State{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	STAY,
	COMBAT,
	FOLLOW,
	PATHWALK
	};
	
	State myDirection;
	State myAI;

	SpriteExt mySprite;
	sf::Image myTexture;

	sf::Vector2i myPosition;
	sf::Vector2i target;
	sf::Vector2i heroPosition;
	sf::Vector2f shiftVector;

public:

	void Display(sf::RenderWindow *window);
	void Logic(sf::Vector2i Target);
	int GoToPosition(sf::Vector2i Destination);
	
	void AI();
	void SetStartPosition(sf::Vector2f Position);
	void SetPathPoints(std::vector<sf::Vector2i> *Path);
	Enemy(sf::Vector2i Position = sf::Vector2i(300,300),std::string fileName = "Pirate.PNG" ,
		float Velocity = 1.0 , float PullRange = 200.0 );
	~Enemy(void);

	void SetHeroPosition( sf::Vector2f HeroPosition );
};
