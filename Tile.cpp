#include "Tile.h"

Tile::Tile(int _type, int pos_x, int pos_y)
{
	type = _type;
	drawingPosition.x = pos_x;
	drawingPosition.y = pos_y;

}

Tile::Tile()
{
	type = -1;
}

void Tile::loadSetOfGraphics(const std::string& filename)
{
	tileTexture = ImageManager::getInstance()->loadImage( filename );
	tileTexture.CreateMaskFromColor(sf::Color(255,0,255));

	//tileSprite.SetImage( tileTexture );
   // tileSprite.SetScale( 1, 1 ); 
	//tileSprite.SetPosition( 0, 0 );
}

Tile::Tile(int _type, const std::string& filename)
{
	type = _type;
	loadSetOfGraphics(filename);
}

int Tile::getType()
{
	return type;
}

sf::Vector2i Tile::getPosition()
{
	return drawingPosition;
}