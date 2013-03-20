#pragma once
#include <SFML/Graphics.hpp>
#include "Missle.h"
#ifndef WEAPON_H
#define WEAPON_H
class Weapon
{
private:
	float cooldown;
	double damage;
	int bulletFireLimit;
	int bulletLeft;
	float repeatRate;			 //Czêstotliwoœæ strza³ów przy wciœniêtym spuœcie
	float distanceFromMouse;

	sf::Vector2f destenation;
	sf::Vector2f fireFromPosition;
	sf::Clock repetition;
	const sf::Input &steering;
	Missle **missle;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
public:
	bool fired;
	Weapon(const sf::Input &_steering, int BulletFireLimit = 5,float RepeatRate = 0.25);
	~Weapon(void);
	void WeaponFiring();
	void Display(sf::RenderWindow *window);
	void Logic();
	void SetFiringPosition(sf::Vector2f Position);
	void SetTargetPosition(sf::Vector2f Position);
	void PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	int ReturnFirstAvailable(Missle **missle,int MissleAmount );
};

#endif