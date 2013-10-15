#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_
#include <map>
#include <string>
#include <SFML/Audio.hpp>

class SoundBufferManager
{
private:

	static SoundBufferManager* INSTANCE;
	std::map<std::string, sf::SoundBuffer> images;
	sf::SoundBuffer buffer_empty;

public:

	static SoundBufferManager* getInstance();
	sf::SoundBuffer& loadSound( std::string filename );
};

#endif /* SOUNDMANAGER_H_ */
