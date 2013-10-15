#pragma once
#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Drawable.h"
#include "Weapon.h"
#include "Animate.h"
#include "SpriteExt.h"
#include <vector>

class Hero : public Drawable
{
public:
	static const int SPRITE_SIZE  = 32; // 32 bo szerokosc tekstury
	static sf::Vector2f myPosition;	//hero position
private:

	bool fire;
	bool armor; //pancerz
	bool invincible; //niesmiertelnosc

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int weaponType;
	int numberOfWeapons;

	float myDistanceToMouse;
	float velocity;
	float currentVelocity;
	float direction;

	sf::Key::Code keyUp;
	sf::Key::Code keyDown;
	sf::Key::Code keyLeft;
	sf::Key::Code keyRight;

	enum State{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	STAY
};
	State ANIMATION_TYPE;

	Animate **animate;
	Weapon **weapon;
	SpriteExt Me;

	sf::Image MyTexture;			
	sf::String strMyPosition;

const sf::Input &steering;//Interakcja z otoczeniem

public:
	Hero(const sf::Input &_steering,float _velocity = 2); //Konstruktor Bohatera
	~Hero(void);

	sf::Vector2f get_position(){return myPosition;}

	void Display(sf::RenderWindow *window);
	void UpdateSystem();
	void EventHandling();

	void Logic();
	void Move();
	void Shoot();
	void GetEvent();
	sf::Vector2f GetPosition();
	void UpdatePosition();
	void PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);
	void UpdateCollision();

	void SetCamera(sf::View *View, sf::RenderWindow *window);			      //Ustawienie kamery
};
#endif
