#ifndef EFFECTLAYER_H_
#define EFFECTLAYER_H_
#include "../Singleton.h"
#include <queue>
#include <string>
#include <SFML/Graphics.hpp>

namespace Fx
{
	enum
	{
		HeroDeath,
		Grayscale
	};
}

class EffectLayer : public Singleton<EffectLayer>
{
private:
	std::queue<sf::PostFX*> effects_queue;
	std::string paths[2];
public:
	EffectLayer();
	sf::PostFX& AddEffect(unsigned int);
	void DrawEffects();
};

#endif /* EFFECTLAYER_H_ */
