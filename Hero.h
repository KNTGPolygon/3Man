#pragma once
#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Animate.h"
#include "SpriteExt.h"
#include <vector>

class Hero
{
public:
	static const int SPRITE_SIZE  = 42; // 42 bo szerokosc tekstury
private:
	bool fire;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int weaponType;
	int numberOfWeapons;
	float myDistanceToMouse;
	float vel;	

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
	sf::Vector2f myPosition;	//hero position
	//sf::Sprite Me;
	SpriteExt Me;
	sf::IntRect box;			//Collision box
	sf::Image MyTexture;			
	sf::String strMyPosition;	

const sf::Input &steering;//Interakcja z otoczeniem

public:
	Hero(const sf::Input &_steering,float velocity = 1); //Konstruktor Bohatera
	~Hero(void);

	sf::IntRect get_box() {return box;} //Zwraca colision boxa
	sf::Vector2f get_position(){return myPosition;}

	void Display(sf::RenderWindow *window);

	void Logic();
	void Move();
	void Shoot();
	void GetEvent();
	sf::Vector2f GetPosition();
	void UpdatePosition();
	void PutScreenSize(int _SCREEN_WIDTH, int _SCREEN_HEIGHT);

	void SetCamera(sf::View *View, sf::RenderWindow *window);			      //Ustawienie kamery
};
#endif
