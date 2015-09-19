#include "ArtificialIntelligence.h"


ArtificialIntelligence::ArtificialIntelligence() : _resetRotation(false)
{
}


ArtificialIntelligence::~ArtificialIntelligence()
{
}


void ArtificialIntelligence::move(Entity* entity, GLfloat speed)
{
	if (_collisionTime + TimeToEscape < glfwGetTime())
	{
		//go to camera
		moveToCamera(entity, speed);
	}
	else
	{
		//go somewhere else
		moveSomewhere(entity, speed);
	}
}



void ArtificialIntelligence::moveSomewhere(Entity* entity, GLfloat speed)
{
	entity->setVelocity(_returnSpeed);
}



void ArtificialIntelligence::moveToCamera(Entity* entity, GLfloat speed)
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
	if (!_resetRotation)
	{
		vec2 u = oldVelocity;
		vec2 v = vec2(entity->getVelocity().x, entity->getVelocity().z);
		GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
		entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	}
	else
	{
		//reset
		vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
		vec2 v = normalize(vec2(cameraPosition.x, cameraPosition.y) - vec2(entity->getPosition().x, entity->getPosition().z));
		GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
		entity->setRotation(makeVector3(0.0f, angle, 0.0f));
		_resetRotation = false;
	}
}


void ArtificialIntelligence::moveWhenCollision(Entity *entity, GLfloat speed)
{


	vec2 movementDir = - vec2(entity->getMovementDirection().x, entity->getMovementDirection().z);
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
	//_returnSpeed = entity->getVelocity();


	vec2 u2 = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat angle2 = rand() % 90 + 1;

	if (rand() % 1 + 1 == 0)
		angle = -1 * angle;

	vec2 returnSpeed = -vec2(u2.x * cos(glm::radians(angle2)) - u2.y * sin(glm::radians(angle2)), u2.x * sin(glm::radians(angle2)) + u2.y * cos(glm::radians(angle2)));
	_returnSpeed = makeVector3(returnSpeed.x, 0.0f, returnSpeed.y);
	_resetRotation = true;
}