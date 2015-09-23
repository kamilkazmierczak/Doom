#include "MovementSystem.h"
#include "EnvironmentReactions.h"

MovementSystem::MovementSystem()
{
}


MovementSystem::~MovementSystem()
{
}


void MovementSystem::update(vector<Entity*> *entityArray)
{
	Player *player = &Player::getPlayer();
	EnvironmentReactions *environment = &EnvironmentReactions::getEnvironmentReactions();

	if (player->getHealth() > 0 && !environment->getAllEnemyDeadStatus())
	{
		for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end(); iterator++)
		{
			Entity *entity = *iterator;
			Vector3 oldPosition = entity->getPosition();

			entity->setPosition(addVector3(entity->getPosition(), entity->getVelocity()));
			entity->setScale(addVector3(entity->getScale(), entity->getScaleVelocity()));
			entity->setRotation(addVector3(entity->getRotation(), entity->getRotationVelocity()));

			vec3 movementDirection = normalize(vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z)
				- vec3(oldPosition.x, oldPosition.y, oldPosition.z));
			entity->setMovementDirection(makeVector3(movementDirection.x, movementDirection.y, movementDirection.z));
		}
	}
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