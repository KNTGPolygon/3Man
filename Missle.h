#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "ImageManager.h"
#include "Util.h"
#include "SpriteExt.h"
#ifndef MISSLE_H
#define MISSLE_H

#define PI 3.14159265
class Missle
{
private:
	bool colisionWithiObiect;
	float angle;
	float currentDistance;		 //Chwilowa odleg�o�� od strzelaj�cego
	float range;				 //Zasi�g pocisku
	float velocity;				 //Pr�dko�� pocisku
	float distanceFromTarget;	 // Odleg�o�� od celu ( kliku myszki )
	
	std::string missleColider;

	sf::Image myTexture;
	SpriteExt mySprite;

	sf::Vector2f startPosition;  //Wsp miejsca wystrza�u
	sf::Vector2f currentPosition; 
	sf::Vector2i targetPosition; //Pozycja docelowa
public:
	bool inMove;
	float ReturnAngle();
	void Logic();
	void UpdateCollision();
	void Display(sf::RenderWindow *window);
	Missle(std::string fileName,std::string _missleColider = "enemy" ,float Range = 10,float Velocity = 1);
	~Missle(void);
	void SetTarget(sf::Vector2i DesignatedPosition,float DistanceFromMouseClick );
	void SetMissleColider( std::string _missleColider );
	void StartPosition(sf::Vector2f Position);
};
#endif
