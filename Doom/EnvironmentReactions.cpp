#include "EnvironmentReactions.h"


EnvironmentReactions::EnvironmentReactions() :_deadDalekNumber(0), _allEnemyDead(false)
{
}


EnvironmentReactions::~EnvironmentReactions()
{
}


void EnvironmentReactions::react()
{
	takeAmmo();
	createWave();
}


void EnvironmentReactions::createWave()
{
	static int nrOfDeadDaleks = 0;
	static int portal = 0;
	static int dalekArray = 2; //bo dwa sa tworzone przez scene ten bd 3

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
				dalekPostion = vec3(-5.0f, -1.5f, -8.5f); //to tez powinno byc pobrane a nie recznie
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
			Entity *entity = new Entity(model, makeVector3(dalekPostion.x, dalekPostion.y, dalekPostion.z), ENTITY_ENEMY);
			vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
			vec2 v = normalize(vec2(cameraPos.x, cameraPos.z) - vec2(entity->getPosition().x, entity->getPosition().z));
			GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
			entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
			entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
			renderSystem->getNewObjects()->push_back(entity);

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

	//To powinno byc inaczej powinien sam sobie pobrac informacje gdzie jest bron
	//ale to tylko jedna reakcja na bron wiec moze tak byc
	vec3 gunPosition = vec3(8.7f, -0.3f, -1.2f);
	GLfloat gunReactRadius = 1.5f;

	GLfloat distance_ = glm::distance(gunPosition, cameraPosition);

	if (distance_ < gunReactRadius && player->getAmmo()<=0)
	{
		//Player *player = &Player::getPlayer();
		player->setAmmo(MaxAmmo);
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