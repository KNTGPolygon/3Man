#include "Drawable.h"

Drawable::Drawable()
{
}

void Drawable::Display(sf::RenderWindow* window)
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

