#ifndef SOUNDPLAYER_H_
#define SOUNDPLAYER_H_
#include <SFML/Audio.hpp>
#include <string>
#include "../Singleton.h"

namespace Snd
{
	enum
	{
		Shoot,
		MenuSelect,
		EnemyDeath,
		HeroDeath,
		GunUpgrade,
		ArmorUpgrade,
		ArmorDestroy
	};
}

class SoundPlayer : public Singleton<SoundPlayer>
{
private:

	std::string paths[7];
	sf::Sound sounds[7];

public:
	SoundPlayer();
	void Play( unsigned int );
};

#endif /* SOUNDPLAYER_H_ */
