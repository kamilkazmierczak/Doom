#pragma once

//#include <vector>
//#include <algorithm>
//#include "ShaderInterface.h"
//#include "VertexBuffer.h"
//#include "ResourceManager.h"
//#include "Entity.h"
//#include "CameraSystem.h"
//#include "RenderSystem.h"
//#include "SphereObject.h"
//// GLM Mathematics
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <GLFW/glfw3.h>

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
	//GLfloat _angle;

	void moveToCamera(Entity* entity, GLfloat speed);
	void moveSomewhere(Entity* entity, GLfloat speed);

public:

	void move(Entity* entity, GLfloat speed);
	void moveWhenCollision(Entity *entity, GLfloat speed);


	EnemyIntelligence();
	~EnemyIntelligence();

};
