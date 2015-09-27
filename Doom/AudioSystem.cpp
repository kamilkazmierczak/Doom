#include "AudioSystem.h"


AudioSystem::AudioSystem()
{
	cout << "wywolana" << endl;
}


AudioSystem::~AudioSystem()
{
	
}

ISoundEngine* AudioSystem::_engine = createIrrKlangDevice();
map<string, string>* AudioSystem::_audioFiles = new map<string, string>();
ISound* AudioSystem::_music = nullptr;

AudioSystem& AudioSystem::getAudioSystem()
{
	static AudioSystem *audioSystem = NULL;

	if (audioSystem == NULL){

		//_engine = createIrrKlangDevice();
		if (!_engine)
			cout << "Error starting up the engine" << endl;

		//_audioFiles = new map<string, string>();
		_audioFiles->insert(pair<string, string>("exterminate", "Audio/exterminate.mp3"));
		_audioFiles->insert(pair<string, string>("r2d2a", "Audio/r2d2a.mp3"));
		_audioFiles->insert(pair<string, string>("r2d2b", "Audio/r2d2b.mp3"));
		_audioFiles->insert(pair<string, string>("r2d2c", "Audio/r2d2c.mp3"));
		_audioFiles->insert(pair<string, string>("plane", "Audio/engine.mp3"));
		_audioFiles->insert(pair<string, string>("gunshoot", "Audio/gunshoot.mp3"));
		_audioFiles->insert(pair<string, string>("enemyhit", "Audio/hit.mp3"));
		_audioFiles->insert(pair<string, string>("antimatter", "Audio/antimatter.mp3"));
		_audioFiles->insert(pair<string, string>("playerhit", "Audio/playerhit.mp3"));
		_audioFiles->insert(pair<string, string>("gameover", "Audio/gameover.mp3"));
		_audioFiles->insert(pair<string, string>("victory", "Audio/victory.mp3"));

		audioSystem = new AudioSystem();
	}

	return *audioSystem;
}

void AudioSystem::destroyAudioSystem()
{
	AudioSystem *audioSystem = &getAudioSystem();
	_engine->drop();

	if (_music)
		_music->drop();

	delete audioSystem;
}

void AudioSystem::playSample()
{
	//_engine->play2D("Audio/exterminate.mp3",true);

	/*map<string, string>::iterator it = _audioFiles->find("exterminate");
	char* patch = new char[it->second.length() + 1];
	strcpy_s(patch, it->second.length() + 1, it->second.c_str());*/


	

}

void AudioSystem::playShoot()
{
	_engine->play2D(findPatch("gunshoot"));
}
  
void AudioSystem::playEnemyHit(vec3 position, vec3 cameraPosition, vec3 cameraDirection)
{
	_music = _engine->play3D(findPatch("enemyhit"), vec3df(0, 0, 0), false, false, true);
	_music->setMinDistance(1.0f);
	_engine->setListenerPosition(vec3df(cameraPosition.x, 0, cameraPosition.z), vec3df(-cameraDirection.x, -cameraDirection.y, -cameraDirection.z));
	_music->setPosition(vec3df(position.x, position.y, position.z));
}

void AudioSystem::playEnemyCreate(vec3 position, vec3 cameraPosition, vec3 cameraDirection)
{
	_music = _engine->play3D(findPatch("antimatter"), vec3df(0, 0, 0), false, false, true);
	_music->setMinDistance(10.0f);
	_engine->setListenerPosition(vec3df(cameraPosition.x, 0, cameraPosition.z), vec3df(-cameraDirection.x, -cameraDirection.y, -cameraDirection.z));
	_music->setPosition(vec3df(position.x, position.y, position.z));
}


void AudioSystem::playPlayerHit()
{
	_engine->play2D(findPatch("playerhit"));
}


void AudioSystem::playGameOver()
{
	_engine->play2D(findPatch("gameover"));
}

void AudioSystem::playVictory()
{
	_engine->play2D(findPatch("victory"));
}

void AudioSystem::stopAllSounds()
{
	_engine->stopAllSounds();
}

void AudioSystem::play2DAudio()
{
	//_engine->play2D(findPatch("exterminate"), true);
}

void AudioSystem::play3DAudio()
{
	//
}

char* AudioSystem::findPatch(string audioName)
{
	map<string, string>::iterator it = _audioFiles->find(audioName);
	char* patch = new char[it->second.length() + 1];
	strcpy_s(patch, it->second.length() + 1, it->second.c_str());

	return patch;
}