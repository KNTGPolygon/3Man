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
	float angle;
	float currentDistance;		 //Chwilowa odleg�o�� od strzelaj�cego
	float range;				 //Zasi�g pocisku
	float velocity;				 //Pr�dko�� pocisku
	float distanceFromTarget;	 // Odleg�o�� od celu ( kliku myszki )
	
	sf::Image myTexture;
	sf::Sprite mySprite;

	sf::Vector2f startPosition;  //Wsp miejsca wystrza�u
	sf::Vector2f currentPosition; 
	sf::Vector2i targetPosition; //Pozycja docelowa
public:
	bool inMove;
	float ReturnAngle();
	void Logic();
	void Display(sf::RenderWindow *window);
	Missle(std::string fileName,float Range = 10,float Velocity = 1);
	~Missle(void);
	void SetTarget(sf::Vector2i DesignatedPosition,float DistanceFromMouseClick );
	void StartPosition(sf::Vector2f Position);
};
#endif
