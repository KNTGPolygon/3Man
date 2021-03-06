#pragma once
#include "Enemies/Enemy.h"
#include "Drawable.h"
class Number : public Enemy//protected
{
private:
	int value;
	sf::Shape sign;
	bool isMinus;
public:
	Number(sf::Vector2i Position = sf::Vector2i(300,300),int Value = 1,
		bool RandomPathMode =  true,float Velocity = 1.0 , float PullRange = 100.0 );
	~Number(void);
	void Colliding(bool minusCollision,bool plusCollision);
	void UpdateCollision();
	void UpdateSystem();
	void Display(sf::RenderWindow *window);
	void SetImage(int Value);

};
