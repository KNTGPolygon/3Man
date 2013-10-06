#include "EffectManager.h"

sf::PostFX& EffectManager::loadEffect( std::string filename )
{
	for ( std::map<std::string, sf::PostFX>::iterator i = effects.begin(); i != effects.end(); ++i  )
		if ( i->first == filename )
			return i->second;
	sf::PostFX eff;
	if ( eff.LoadFromFile( filename ) )
	{
		effects[filename] = eff;
		return effects[filename];
	}
	else
		return effect_empty;
}
