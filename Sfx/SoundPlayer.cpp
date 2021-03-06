#include "SoundPlayer.h"
#include <stdlib.h>
#include "SoundBufferManager.h"
#include "../GameEngine.h"


SoundPlayer::SoundPlayer()
{
	paths[0] = "Data/Sounds/shooting.wav";
	paths[1] = "Data/Sounds/menu_select.wav";
	paths[2] = "Data/Sounds/enemydeath.wav";
	paths[3] = "Data/Sounds/hero_death.wav";
	paths[4] = "Data/Sounds/gun.wav";
	paths[5] = "Data/Sounds/armor.wav";
	paths[6] = "Data/Sounds/armor_destroy.wav";

	for ( int i = 0; i < 7; i++ )
		sounds[i].SetBuffer( SoundBufferManager::getInstance()->loadSound(paths[i]) );
}

void SoundPlayer::Play( unsigned int id )
{
	if ( GameEngine::getInstance()->Sounds() )
		sounds[id].Play();
}

