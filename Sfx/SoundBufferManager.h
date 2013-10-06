#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_
#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "../Singleton.h"

class SoundBufferManager : public Singleton<SoundBufferManager>
{
private:
	std::map<std::string, sf::SoundBuffer> images;
	sf::SoundBuffer buffer_empty;

public:
	sf::SoundBuffer& loadSound( std::string filename );
};

#endif /* SOUNDMANAGER_H_ */
