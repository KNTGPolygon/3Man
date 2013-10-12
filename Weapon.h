#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Drawable.h"
#include "Missle.h"
#ifndef WEAPON_H
#define WEAPON_H

	enum WeaponType{
		Integral,
		Derivative,
		Minus,
		Plus,
		YellowBall
	};

class Weapon : public Drawable
{
private:

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int bulletFireLimit;
	int bulletLeft;

	float cooldown;
	float distanceFromMouse;

	int error;
	double damage;
	double range;
	double speed;	
	double repeatRate;
	
	std::string missleColider;
	std::string directory;

	sf::Vector2i destenation;
	sf::Vector2f fireFromPosition;
	sf::Clock repetition;
	Missle **missle;

	
public:
	bool fired;
	bool active;
	Weapon(WeaponType weaponType = Integral ,int BulletFireLimit = 5,float RepeatRate = 0.25);
	~Weapon(void);
	
    int ReturnFirstAvailable(Missle **missle,int MissleAmount );

	void WeaponFiring();
	void Display(sf::RenderWindow *window);
	void Logic(bool FiringLocked = false, sf::Vector2i target = sf::Vector2i(0,0));
	void UpdateCollision();
	void SetFiringPosition(sf::Vector2f Position);
	void SetTargetPosition(sf::Vector2f Position);
	void PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	int SetWeapon(WeaponType Weapon);
	
};

#endif
