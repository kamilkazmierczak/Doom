#pragma once

#include <vector>
#include <algorithm>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "CameraSystem.h"
#include "RenderSystem.h"
#include "SphereObject.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


class IArtificialIntelligence
{
protected:


public:
	virtual void move(Entity* entity, GLfloat speed) =0;
	virtual void moveWhenCollision(Entity *entity, GLfloat speed) =0;

	IArtificialIntelligence();
	virtual ~IArtificialIntelligence();
};

