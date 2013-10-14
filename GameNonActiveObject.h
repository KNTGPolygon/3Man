#pragma once

#ifndef NONACTIVE_OBJECT_H
#define NONACTIVE_OBJECT_H

#include "GameObject.h"

class GameNonActiveObject : public GameObject
{

public:
	GameNonActiveObject();
	GameNonActiveObject(float, float, int _type, std::string imageFilePath);
	void EventHandling();
	void Update();
	void Display(sf::RenderWindow*);

};

#endif