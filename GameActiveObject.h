#pragma once

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "GameObject.h"
enum TrapType {BULLET_TOWER, LASER_TOWER, SPIKES};

class GameActiveObject : public GameObject
{
	TrapType trapType;

	sf::Image upTexture;
	SpriteExt upSprite;

	sf::Image shotTexture;
	SpriteExt shotSprite;
	int shootCooldown;
	int laserExistanceTime;
	sf::Vector2i shootDirection;

	int arrayOfOccupiedFieldsSize;
	int ** arrayOfFieldsOccupiedWithObjects;

	int distanceOfHeroTargeting;
	bool targetingHero;
	bool chargingAttack;

	sf::Vector2i targetRotationAndDirection;
	int rotationCooldown;




	public:
	GameActiveObject();
	GameActiveObject(float, float, int _type, std::string imageFilePath, int ** arrayOfFieldsOccupiedWithObj, int objectArraySize);
	void EventHandling();
	void UpdateSystem();
	void Display(sf::RenderWindow*);
	int Display_howLongShouldTheLaserBe();
	void doSomeAnimations();

	void targetHero(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns);
	void targetHero_checkWhichWayToTurn();
	void targetHero_decideOnAngle(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns);
	void attackHero();

	void doSomeAnimations_DecideOnNewTargetAngle();
	void doSomeAnimations_CountShortestRotationPath();


};

#endif