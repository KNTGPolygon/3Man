#include "GameObject.h"

GameObject::GameObject()
{

}

void GameObject::UpdateSystem()
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