#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "ImageManager.h"
#include "Functions.h"
#ifndef MISSLE_H
#define MISSLE_H

#define PI 3.14159265
class Missle
{
private:
	float currentDistance;		 //Chwilowa odleg³oœæ od strzelaj¹cego
	float range;				 //Zasiêg pocisku
	float velocity;				 //Prêdkoœæ pocisku
	float distanceFromTarget;	 // Odleg³oœæ od celu ( kliku myszki )
	
	sf::Image myTexture;
	sf::Sprite mySprite;

	sf::Vector2f startPosition;  //Wsp miejsca wystrza³u
	sf::Vector2f currentPosition; 
	sf::Vector2i targetPosition; //Pozycja docelowa

	

public:
	float angle;
	sf::String strAngle;
	bool inMove;
	void Logic();
	void Display(sf::RenderWindow *window);
	Missle(std::string fileName,float Range = 10,float Velocity = 1);
	~Missle(void);
	void SetTarget(sf::Vector2i DesignatedPosition,float DistanceFromMouseClick );
	void StartPosition(sf::Vector2f Position);
};
#endif
