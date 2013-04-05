#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Missle.h"
#ifndef WEAPON_H
#define WEAPON_H
class Weapon : public Drawable
{
private:
	double damage;
	double range;
	double speed;
	double error;
	double repeatRate;

	int bulletFireLimit;
	int bulletLeft;

	float cooldown;
			 //Cz�stotliwo�� strza��w przy wci�ni�tym spu�cie
	float distanceFromMouse;
	std::string directory;

	sf::Vector2i destenation;
	sf::Vector2f fireFromPosition;
	sf::Clock repetition;
	Missle **missle;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool Load(std::string WeaponName);
public:
	bool fired;
	bool active;
	Weapon(std::string weaponName,int BulletFireLimit = 5,float RepeatRate = 0.25);
	~Weapon(void);
	
    int ReturnFirstAvailable(Missle **missle,int MissleAmount );

	void WeaponFiring();
	void Display(sf::RenderWindow *window);
	void Logic(bool FiringLocked = false, sf::Vector2i target = sf::Vector2i(0,0));
	void SetFiringPosition(sf::Vector2f Position);
	void SetTargetPosition(sf::Vector2f Position);
	void PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	
};

#endif
