#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#ifndef MISSLE_H
#define MISSLE_H

class Missle
{
private:
	float currentDistance;		 //Chwilowa odleg³oœæ od strzelaj¹cego
	float range;				 //Zasiêg pocisku
	float velocity;				 //Prêdkoœæ pocisku
	float distanceFromTarget;	 // Odleg³oœæ od celu ( kliku myszki )

//	sf::Clock time;			     //Timer do lotu pocisku (nieuzyty)
	sf::Shape bullet;			 //Tymczasowy kszta³t pocisku

	sf::Vector2f startPosition;  //Wsp miejsca wystrza³u
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
