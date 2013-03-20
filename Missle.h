#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#ifndef MISSLE_H
#define MISSLE_H

class Missle
{
private:
	float currentDistance;		 //Chwilowa odleg�o�� od strzelaj�cego
	float range;				 //Zasi�g pocisku
	float velocity;				 //Pr�dko�� pocisku
	float distanceFromTarget;	 // Odleg�o�� od celu ( kliku myszki )

//	sf::Clock time;			     //Timer do lotu pocisku (nieuzyty)
	sf::Shape bullet;			 //Tymczasowy kszta�t pocisku

	sf::Vector2f startPosition;  //Wsp miejsca wystrza�u
	sf::Vector2f currentPosition; 
	sf::Vector2f targetPosition; //Pozycja docelowa

public:
	bool inMove;
	void Logic();
	void Display(sf::RenderWindow *window);
	Missle(float Range = 10,float Velocity = 1);
	~Missle(void);
	void SetTarget(sf::Vector2f DesignatedPosition,float DistanceFromMouseClick );
	void StartPosition(sf::Vector2f Position);
};
#endif
