#include "State.h"
#include "Hero.h"
#include "Maps.h"
#include "Levels/Wall.h"
#include "Enemy.h"
#include "Number.h"
#include "Collision/QuadtreeNode.h"
#include "Enemies/PathFinder.h"
#include <string>

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState : public State
{
private:
	int counter;
	int path;
	sf::Vector2i lastPath[2];
	std::vector<Drawable*> DrawableEntityList;
	Hero* hero;
	Maps* map;
	std::string current_level;

	Enemy* pirate;

	int iterator;
	int mapPixelatedSize;
	int numberOfObjects;
	GameObject ** arrayOfObjects;
	static const int NUM_OF_ENEMIES = 5;
public:
	static bool restart_level;
	static bool death_effect;
	static sf::Clock death_anim_timer;
public:
	GameState();
	void Init();
	void Display();
	void UpdateSystem();
	void EventHandling();
	void GetEvents();
	void Cleanup();
	void LoadLevel(const std::string&);
	void ClearLevel();
	void HeroDeathEffect();
};

#endif
