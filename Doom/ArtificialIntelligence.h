#pragma once

#include <vector>
#include <algorithm>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "CameraSystem.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;

class ArtificialIntelligence
{
private:

	ArtificialIntelligence();
	~ArtificialIntelligence();
public:

	void moveToCamera(Entity* entity, GLfloat speed);

	static ArtificialIntelligence& getArtificialIntelligence();
	static void destroyArtificialIntelligence();


};

