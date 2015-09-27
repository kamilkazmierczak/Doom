#include "R2D2Audio.h"

//#include <glm/gtc/matrix_transform.hpp>


R2D2Audio::R2D2Audio() : _delay(9.0f) ,_lastPlayTime(0.0f)
{
}


R2D2Audio::~R2D2Audio()
{
	if (_music)
		_music->drop();
}

void R2D2Audio::play3DAudio(vec3 position, vec3 cameraPosition, vec3 cameraDirection)
{

	if(_lastPlayTime + _delay < glfwGetTime())
	{
		_lastPlayTime = glfwGetTime();
		GLfloat random = rand() % 3 + 1;

		if (random == 0)
			_music = _engine->play3D(findPatch("r2d2a"), vec3df(0, 0, 0), false, false, true);
		if (random == 1)
			_music = _engine->play3D(findPatch("r2d2b"), vec3df(0, 0, 0), false, false, true);
		else 
			_music = _engine->play3D(findPatch("r2d2c"), vec3df(0, 0, 0), false, false, true);

		_music->setMinDistance(2.0f);
		_engine->setListenerPosition(vec3df(cameraPosition.x, 0, cameraPosition.z), vec3df(-cameraDirection.x, -cameraDirection.y, -cameraDirection.z));
		_music->setPosition(vec3df(position.x, position.y, position.z));
	
	}

}
