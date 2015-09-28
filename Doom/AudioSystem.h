#pragma once
#include <iostream>
#include <map>
#include <irrKlang/irrKlang.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
//#include "CameraSystem.h"

using namespace irrklang;
using namespace std;
using namespace glm;

class AudioSystem
{
private:
	static ISound* _music;

protected:
	static ISoundEngine* _engine;
	static map<string, string> *_audioFiles;
	char* findPatch(string audioName);

	AudioSystem();
	virtual ~AudioSystem();
public:

	void playShoot();
	void playEnemyHit(vec3 position);
	void playEnemyCreate(vec3 position);
	void playPlayerHit();
	void playGameOver();
	void playVictory();
	void playVictoryGameOver();
	void playReload();
	void playMusic(vec3 position);

	void stopAllSounds();
	void updateListenerPosition(vec3 cameraPosition, vec3 cameraDirection);
	void playSample();
	static AudioSystem& getAudioSystem();
	static void destroyAudioSystem();
};

