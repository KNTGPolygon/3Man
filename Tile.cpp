#include "Tile.h"

Tile::Tile(int _type)
{
	type = _type;

}

Tile::Tile()
{
	type = -1;
}

void Tile::loadSetOfGraphics(const std::string& filename)
{
	MyTexture.LoadFromFile( "Data/Textures/something.bmp" );
	MyTexture.CreateMaskFromColor(sf::Color(255,0,255));
}