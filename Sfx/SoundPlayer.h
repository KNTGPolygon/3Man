#ifndef SOUNDPLAYER_H_
#define SOUNDPLAYER_H_
#include <SFML/Audio.hpp>
#include <string>

namespace Snd
{
	enum
	{
		Shoot,
		MenuSelect,
		EnemyDeath,
		HeroDeath,
		GunUpgrade,
		ArmorUpgrade
	};
}

class SoundPlayer
{
private:
	static SoundPlayer* INSTANCE;
	std::string paths[7];
	sf::Sound sounds[7];

public:
	SoundPlayer();
	void Play( unsigned int );
	static SoundPlayer* getInstance();
};

#endif /* SOUNDPLAYER_H_ */
