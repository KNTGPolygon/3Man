#include "ImageManager.h"
#include <stdlib.h>
#include <string>
#include <SFML/Graphics.hpp>

ImageManager* ImageManager::INSTANCE = NULL;

ImageManager* ImageManager::getInstance()
{
		if ( INSTANCE == NULL )
			INSTANCE = new ImageManager();
		return INSTANCE;
}

sf::Image& ImageManager::loadImage( std::string filename )
{
	for ( std::map<std::string, sf::Image>::iterator i = images.begin(); i != images.end(); ++i  )
		if ( i->first == filename )
			return i->second;
	sf::Image img;
	if ( img.LoadFromFile( filename ) )
	{
		images[filename] = img;
		return images[filename];
	}
}
