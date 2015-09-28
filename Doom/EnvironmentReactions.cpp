#include "EnvironmentReactions.h"
#include "EnemyAudio.h"
#include "GameManager.h"
#include "LevelSystem.h"


EnvironmentReactions::EnvironmentReactions() :_deadDalekNumber(0), _allEnemyDead(false), _resetInformation(false), _gameOver(false),
_audioSystem(&AudioSystem::getAudioSystem())
{
}


EnvironmentReactions::~EnvironmentReactions()
{
}


void EnvironmentReactions::react()
{
	takeAmmo();
	createWave();
	playSounds();
}

void EnvironmentReactions::playSounds()
{
	Player *player = &Player::getPlayer();
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	LevelSystem *levelSystem = &LevelSystem::getLevelSystem();

	_audioSystem->updateListenerPosition(cameraSystem->getCurrentCamera()->getPosition(), cameraSystem->getCurrentCamera()->getCenter());


	if (!_gameOver)
	{
		if (_allEnemyDead == true)
		{//Victory
			_audioSystem->stopAllSounds();
			_gameOver = true;

			levelSystem->setLevel(levelSystem->getCurrentLevel() + 1);

			if (levelSystem->getFinalRoundStatus())		
				_audioSystem->playVictoryGameOver();	
			else
				_audioSystem->playVictory();

		}
		else if (player->getHealth() <= 0.0f)
		{//GameOver
			_audioSystem->stopAllSounds();
			_audioSystem->playGameOver();
			_gameOver = true;
		}
	}
}



void EnvironmentReactions::resetInformation()
{
	_resetInformation = true;
	_allEnemyDead = false;
	_deadDalekNumber = 0;
	_gameOver = false;

	//AudioSystem *audioSystem = &AudioSystem::getAudioSystem();
	_audioSystem->stopAllSounds();
}


void EnvironmentReactions::createWave()
{
	static int nrOfDeadDaleks = 0;
	static int portal = 0;
	static int dalekArray = 2; //bo dwa sa tworzone przez scene ten bd 3


	if (_resetInformation)
	{
		nrOfDeadDaleks = 0;
		portal = 0;
		dalekArray = 2;
		_resetInformation = false;
	}


	if (_deadDalekNumber >= NumberOfDaleks - 1)
	{
		if (_deadDalekNumber >= NumberOfDaleks)
			_allEnemyDead = true;
	}
	else //sprawdz czy jest koniecznosc i wygeneruj dalka
	{
		if (_deadDalekNumber != nrOfDeadDaleks)
		{
			//zginal nowy dalek, stworz nowego dalka
			int portalNr = portal % 2; //0,1
			vec3 dalekPostion;
			if (portalNr == 0)
			{
				dalekPostion = vec3(-5.0f, -1.5f, -8.5f); 
			}
			else
			{
				dalekPostion = vec3(5.0f, -1.5f, -8.5f);
			}

			//tworzenie dalka
			ResourceManager *resourceManager = &ResourceManager::getResourceManager();
			RenderSystem *renderSystem = &RenderSystem::getRenderSystem();
			CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
			vec3 cameraPos = cameraSystem->getCurrentCamera()->getPosition();
			IObject *model = new ModelObject(resourceManager->getDalekArray()->at(dalekArray++), new EnemyIntelligence());
			Entity *entity = new Entity(model, makeVector3(dalekPostion.x, dalekPostion.y, dalekPostion.z), ENTITY_ENEMY, new EnemyAudio(glfwGetTime()));
			vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
			vec2 v = normalize(vec2(cameraPos.x, cameraPos.z) - vec2(entity->getPosition().x, entity->getPosition().z));
			GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
			entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
			entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
			renderSystem->getNewObjects()->push_back(entity);

			AudioSystem *audioSystem = &AudioSystem::getAudioSystem();
			vec3 position = vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z);
			audioSystem->playEnemyCreate(position);


			nrOfDeadDaleks++;
			portal++;
		}
		else
		{
			//nic nie rob
		}
	}
}

void EnvironmentReactions::countDalek()
{
	_deadDalekNumber++;
}


void EnvironmentReactions::takeAmmo()
{
	Player *player = &Player::getPlayer();

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	vec3 cameraPosition = cameraSystem->getCurrentCamera()->getPosition();

	vec3 gunPosition = vec3(8.7f, -0.3f, -1.2f);
	GLfloat gunReactRadius = 2.0f;

	GLfloat distance_ = glm::distance(gunPosition, cameraPosition);

	if (distance_ < gunReactRadius && player->getAmmo()<=0)
	{
		player->setAmmo(MaxAmmo);
		_audioSystem->playReload();
	}

}

bool EnvironmentReactions::getAllEnemyDeadStatus()
{
	return _allEnemyDead;
}


EnvironmentReactions& EnvironmentReactions::getEnvironmentReactions()
{
	static EnvironmentReactions *environmentReactions = NULL;

	if (environmentReactions == NULL){
		environmentReactions = new EnvironmentReactions();
	}

	return *environmentReactions;
}

void EnvironmentReactions::destroyEnvironmentReactions()
{
	EnvironmentReactions *environmentReactions = &getEnvironmentReactions();
	delete environmentReactions;
}