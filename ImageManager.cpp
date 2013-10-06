#include "ImageManager.h"
#include <stdlib.h>
#include <string>
#include <SFML/Graphics.hpp>

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
	else
		return image_blank;
}
