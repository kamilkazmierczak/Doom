#include "MovementSystem.h"


MovementSystem::MovementSystem()
{
}


MovementSystem::~MovementSystem()
{
}


void MovementSystem::update(Entity *entity)
{
	entity->setPosition(addVector3(entity->getPosition(), entity->getVelocity()));
	entity->setScale(addVector3(entity->getScale(), entity->getScaleVelocity()));
	entity->setRotation(addVector3(entity->getRotation(), entity->getRotationVelocity()));
}


MovementSystem& MovementSystem::getMovementSystem()
{
	static MovementSystem* movementSystem = NULL;

	if (movementSystem == NULL){
		movementSystem = new MovementSystem();
	}

	return *movementSystem;
}

void MovementSystem::destroyMovementSystem()
{
	MovementSystem* movementSystem = &getMovementSystem();
	delete movementSystem;
}