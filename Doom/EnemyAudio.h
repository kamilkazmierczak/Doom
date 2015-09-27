#pragma once
#include "AudioSystem.h"
using namespace glm;

class EnemyAudio : public AudioSystem
{
private:
	GLfloat _delay;
	GLfloat _lastPlayTime;
	ISound* _music;

public:

	void play3DAudio(vec3 position, vec3 cameraPosition, vec3 cameraDirection);

	EnemyAudio(GLfloat firstPlayTime);
	~EnemyAudio();
};

