#pragma once
#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include <vector>

class Hero
{
public:
	static const int SPRITE_SIZE  = 42; // 42 bo szerokosc tekstury
private:

	float myDistanceToMouse;
	float vel;								
	bool fire;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
Weapon *weapon;

sf::Vector2f myPosition;	//hero position
sf::Sprite Me;				
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