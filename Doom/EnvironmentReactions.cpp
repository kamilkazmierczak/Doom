#include "EnvironmentReactions.h"


EnvironmentReactions::EnvironmentReactions()
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

}




void EnvironmentReactions::takeAmmo()
{

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	vec3 cameraPosition = cameraSystem->getCurrentCamera()->getPosition();

	//To powinno byc inaczej powinien sam sobie pobrac informacje gdzie jest bron
	//ale to tylko jedna reakcja na bron wiec moze tak byc
	vec3 gunPosition = vec3(8.7f, -0.3f, -1.2f);
	GLfloat gunReactRadius = 1.5f;

	GLfloat distance_ = glm::distance(gunPosition, cameraPosition);

	if (distance_ < gunReactRadius)
	{
		Player *player = &Player::getPlayer();
		player->setAmmo(MaxAmmo);
	}

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