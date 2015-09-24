#pragma once

#include "IArtificialIntelligence.h"

using namespace std;
using namespace glm;

class EnemyIntelligence : public IArtificialIntelligence
{
private:

	GLfloat _collisionTime;
	Vector3 _returnSpeed;
	bool _resetRotation;
	void shoot(Entity *entity);

	void moveToCamera(Entity* entity, GLfloat speed);
	void moveSomewhere(Entity* entity, GLfloat speed);

public:

	void move(Entity* entity, GLfloat speed);
	void moveWhenCollision(Entity *entity, GLfloat speed);

	EnemyIntelligence();
	~EnemyIntelligence();

};

