#pragma once
#include "IArtificialIntelligence.h"

using namespace std;
using namespace glm;

class R2D2Intelligence : public IArtificialIntelligence
{
private:


public:

	void move(Entity* entity, GLfloat speed);
	void moveWhenCollision(Entity *entity, GLfloat speed);

	R2D2Intelligence();
	~R2D2Intelligence();
};

