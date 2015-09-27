#include "EnemyAudio.h"


EnemyAudio::EnemyAudio(GLfloat firstPlayTime) : _delay(5.0f), _lastPlayTime(firstPlayTime)
{
}


EnemyAudio::~EnemyAudio()
{
	if (_music)
		_music->drop();
}

void EnemyAudio::play3DAudio(vec3 position, vec3 cameraPosition, vec3 cameraDirection)
{

	if (_lastPlayTime + _delay < glfwGetTime())
	{
		_lastPlayTime = glfwGetTime();

		_music = _engine->play3D(findPatch("exterminate"), vec3df(0, 0, 0), false, false, true);
		_music->setMinDistance(4.0f);
		_engine->setListenerPosition(vec3df(cameraPosition.x, 0, cameraPosition.z), vec3df(-cameraDirection.x, -cameraDirection.y, -cameraDirection.z));
		_music->setPosition(vec3df(position.x, position.y, position.z));

	}

}