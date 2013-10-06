#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_
#include <string>
#include <map>
#include "../Singleton.h"
#include <SFML/Graphics.hpp>

class EffectManager : public Singleton<EffectManager>
{
private:
	std::map<std::string, sf::PostFX> effects;
	sf::PostFX effect_empty;

public:
	sf::PostFX& loadEffect( std::string filename );
};

#endif /* EFFECTMANAGER_H_ */
