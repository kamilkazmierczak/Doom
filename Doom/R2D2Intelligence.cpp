#include "R2D2Intelligence.h"


R2D2Intelligence::R2D2Intelligence()
{
}


R2D2Intelligence::~R2D2Intelligence()
{
}


void R2D2Intelligence::move(Entity* entity, GLfloat speed)
{
	Vector3 velocity = makeVector3(speed, 0.0f, 0.0f);
	
	if (entity->getPosition().x <=-9.0f)
	{
		entity->setRotation(makeVector3(0.0f, 90.0f, 0.0f));
		entity->setVelocity(velocity);
	}
	else if (entity->getPosition().x >= 9.0f)
	{
		velocity.x *= -1;
		entity->setVelocity(velocity);
		entity->setRotation(makeVector3(0.0f, -90.0f, 0.0f));
	}
}

void R2D2Intelligence::moveWhenCollision(Entity *entity, GLfloat speed)
{
	
}