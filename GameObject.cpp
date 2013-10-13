#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject()
{

}

void GameObject::Update()
{

}

void GameObject::Display(sf::RenderWindow * window)
{
	
}

sf::Vector2f GameObject::GetPosition()
{
	return mySprite.GetPosition();
}

int GameObject::getType()
{
	return type;
}