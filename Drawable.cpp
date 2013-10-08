#include "Drawable.h"

Drawable::Drawable()
{
	depth = 0;
}

void Drawable::Display(sf::RenderWindow* window)
{
}

void Drawable::UpdateSystem()
{
}

void Drawable::EventHandling()
{
}

void Drawable::GetEvents()
{
}

void Drawable::setDepth(int _depth)
{
	depth = _depth;
}

int Drawable::getDepth()
{
	return depth;
}

Drawable::~Drawable()
{
}

