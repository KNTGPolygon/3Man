#pragma once
#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include "Functions.h"
#include <vector>

class Hero
{
private:

float Vel;								

sf::Vector2f myPosition;	//hero position
sf::Sprite Me;				
sf::IntRect box;			//Collision box
sf::Image MyTexture;			
sf::String strMyPosition;	


const sf::Input &steering;//Interakcja z otoczeniem

public:
	Hero(sf::Input &_steering,float Velocity = 1); //Konstruktor Bohatera
	~Hero(void);

sf::IntRect get_box() {return box;} //Zwraca colision boxa
sf::Vector2f get_position(){return myPosition;}

void Display(sf::RenderWindow window);
void Move();

void GetEvent();
void GetPosition();

void SetCamera();			      //Ustawienie kamery
};
#endif