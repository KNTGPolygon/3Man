#include "SoundBufferManager.h"
#include <stdlib.h>
#include <string>
#include <SFML/Audio.hpp>

sf::SoundBuffer& SoundBufferManager::loadSound( std::string filename )
{
	for ( std::map<std::string, sf::SoundBuffer>::iterator i = images.begin(); i != images.end(); ++i  )
		if ( i->first == filename )
			return i->second;
	sf::SoundBuffer sndbuff;
	if ( sndbuff.LoadFromFile( filename ) )
	{
		images[filename] = sndbuff;
		return images[filename];
	}
	else
		return buffer_empty;
}
