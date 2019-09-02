#include "SoundManager.h"

SoundManager::SoundManager()
{
	init();
}


SoundManager::~SoundManager()
{

}

void SoundManager::Destroy()
{
	delete fmodSystem;
}

void SoundManager::init()
{
	System_Create(&fmodSystem);
	fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::AddBGM(string path)
{
	fmodSystem->createSound(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm);
}

void SoundManager::AddSFX(string path, string soundName)
{
	fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &soundHash[soundName]);
}

void SoundManager::PlayBGM()
{
	fmodSystem->playSound(bgm, NULL, false, &bgmChannel);
}

void SoundManager::PlaySFX(string soundName)
{
	if (soundHash[soundName] != NULL)
		fmodSystem->playSound(soundHash[soundName], NULL, false, &sfxChannel);
}

void SoundManager::Stop()
{
	sfxChannel->stop();
	bgmChannel->stop();
}