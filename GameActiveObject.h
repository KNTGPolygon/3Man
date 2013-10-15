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

	void doSomeAnimations_DecideOnNewTargetAngle();
	void doSomeAnimations_CountShortestRotationPath();

};

#endif