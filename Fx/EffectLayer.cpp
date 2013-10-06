#include "EffectLayer.h"
#include "EffectManager.h"
#include "../GameEngine.h"

EffectLayer::EffectLayer()
{
	paths[0] = "Data/Effects/HeroDeath.fx";
	paths[1] = "Data/Effects/Grayscale.fx";
}

sf::PostFX& EffectLayer::AddEffect(unsigned int id)
{
	sf::PostFX& ef = EffectManager::getInstance()->loadEffect(paths[id]);
	effects_queue.push(&ef);
	ef.SetTexture("framebuffer", NULL);
	return ef;
}

void EffectLayer::DrawEffects()
{
	while ( !effects_queue.empty() )
	{
		GameEngine::getInstance()->getWindow().Draw(*effects_queue.front());
		effects_queue.pop();
	}
}
