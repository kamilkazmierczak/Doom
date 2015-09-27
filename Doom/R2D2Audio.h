#pragma once
#include "AudioSystem.h"
//#include <glm/glm.hpp>
using namespace glm;

class R2D2Audio : public AudioSystem
{
private:
	GLfloat _delay;
	GLfloat _lastPlayTime;
	ISound* _music;

public:

	void play3DAudio(vec3 position);

	R2D2Audio();
	~R2D2Audio();
};

