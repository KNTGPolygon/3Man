#pragma once

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "GameObject.h"
enum TrapType {SPIKES, BULLET_TOWER, LASER_TOWER};

class GameActiveObject : public GameObject
{
	TrapType trapType;

	public:
	GameActiveObject();
	GameActiveObject(float, float, int _type, std::string imageFilePath);
	void EventHandling();
	void UpdateSystem();
	void Display(sf::RenderWindow*);

};

#endif