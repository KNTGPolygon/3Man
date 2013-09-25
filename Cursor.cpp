#include "Cursor.h"
#include "GameEngine.h"
#include "ImageManager.h"

Cursor::Cursor()
{
	image_crosshair = ImageManager::getInstance()->loadImage("Data/Textures/Cursors/crosshair.png");
	image_crosshair.SetSmooth(false);

	sprite_crosshair.SetImage(image_crosshair);
    sprite_crosshair.SetScale( 1, 1 );
    sprite_crosshair.SetSubRect(sf::IntRect(0,0,25,25));
	sprite_crosshair.SetCenter(12,12);

	image_hand = ImageManager::getInstance()->loadImage("Data/Textures/Cursors/arrow.png");
	image_hand.SetSmooth(false);

	sprite_hand.SetImage(image_hand);
    sprite_hand.SetScale( 1, 1 );
    sprite_hand.SetSubRect(sf::IntRect(0,0,25,25));
	sprite_hand.SetCenter(2,2);

	type = ARROW;
}

void Cursor::Display(sf::RenderWindow* window)
{
	sprite->SetPosition( GameEngine::getInstance()->GetMouseCoords() );
	window->Draw(*sprite);
}

void Cursor::setType( CURSOR_TYPE type )
{
	if ( type == ARROW ) sprite = &sprite_hand;
	else if ( type == CROSSHAIR ) sprite = &sprite_crosshair;
}

