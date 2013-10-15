#pragma once

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "GameObject.h"
enum TrapType {SPIKES, BULLET_TOWER, LASER_TOWER};

class GameActiveObject : public GameObject
{
	TrapType trapType;

	sf::Image upTexture;
	SpriteExt upSprite;

	int distanceOfHeroTargeting;
	bool targetingHero;

	sf::Vector2i targetRotationAndDirection;
	int rotationCooldown;

	public:
	GameActiveObject();
	GameActiveObject(float, float, int _type, std::string imageFilePath);
	void EventHandling();
	void UpdateSystem();
	void Display(sf::RenderWindow*);
	void doSomeAnimations();

	void targetHero(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns);
	void targetHero_checkWhichWayToTurn();
	void targetHero_decideOnAngle(sf::Vector2f distanceBetweenHeroAndTrap, sf::Vector2i distanceSigns);

	void doSomeAnimations_DecideOnNewTargetAngle();
	void doSomeAnimations_CountShortestRotationPath();

};

#endif