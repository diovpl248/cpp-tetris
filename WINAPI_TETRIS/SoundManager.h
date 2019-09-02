#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

using namespace std;
using namespace FMOD;

class SoundManager
{
private:
	System * fmodSystem;

	Channel* bgmChannel;
	Channel* sfxChannel;

	Sound* bgm;
	map<string, Sound*> soundHash;

private:
	void init();

public:
	SoundManager();
	~SoundManager();

	void AddSFX(string path, string musicName);
	void AddBGM(string path);

	void PlaySFX(string soundName);
	void PlayBGM();

	void Stop();

	void Destroy();
};

