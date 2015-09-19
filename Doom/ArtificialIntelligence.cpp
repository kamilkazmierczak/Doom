#include "ArtificialIntelligence.h"


ArtificialIntelligence::ArtificialIntelligence()
{
}


ArtificialIntelligence::~ArtificialIntelligence()
{
}



void ArtificialIntelligence::moveToCamera(Entity* entity, GLfloat speed)
{

	if (_collisionTime + TimeToEscape < glfwGetTime())
	{

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();

	//rotation
	vec2 oldVelocity = vec2(entity->getVelocity().x, entity->getVelocity().z);
	//#rotation
	vec2 cameraPosition = vec2(cameraSystem->getCurrentCamera()->getPosition().x, cameraSystem->getCurrentCamera()->getPosition().z);
	vec2 myPosition = vec2(entity->getPosition().x, entity->getPosition().z);
	vec2 direction = normalize(cameraPosition - myPosition);
	GLfloat max = std::max(std::abs(direction.x), std::abs(direction.y)); //y to tak naprawde z

	if (max != 0)
	{
		entity->setVelocity(makeVector3((direction.x / max) * speed,
			0.0f,
			(direction.y / max) * speed));
	}
	else
	{
		//chyba teraz patrze na srodek
		entity->setVelocity(makeVector3(speed, 0.0f, speed));
	}
	//teraz obrot
	vec2 u = oldVelocity;
	vec2 v = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));

	}
	else
	{
		entity->setVelocity(makeVector3(_returnSpeed.x, _returnSpeed.y, _returnSpeed.z));
	}

}


void ArtificialIntelligence::moveWhenCollision(Entity *entity, GLfloat speed)
{


	vec2 movementDir = -vec2(entity->getMovementDirection().x, entity->getMovementDirection().z);
	vec2 oldVelocity = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat max = std::max(std::abs(movementDir.x), std::abs(movementDir.y)); //y to tak naprawde z


	if (max != 0)
	{
		entity->setVelocity(makeVector3((movementDir.x / max)  * speed,
										 0.0f,
										(movementDir.y / max)  * speed));
	}
	else
	{
		entity->setVelocity(makeVector3(speed, 0.0f, speed));
	}
	//fix rotation
	vec2 u = oldVelocity;
	vec2 v = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));

	_collisionTime = glfwGetTime();
	_returnSpeed = vec3(entity->getVelocity().x, entity->getVelocity().y, entity->getVelocity().z); //tmp
}





ArtificialIntelligence& ArtificialIntelligence::getArtificialIntelligence()
{
	static ArtificialIntelligence *artificialIntelligence = NULL;

	if (artificialIntelligence == NULL){
		artificialIntelligence = new ArtificialIntelligence();
	}

	return *artificialIntelligence;
}

void ArtificialIntelligence::destroyArtificialIntelligence()
{
	ArtificialIntelligence *artificialIntelligence = &getArtificialIntelligence();
	delete artificialIntelligence;
}
