#pragma once
#include <iostream>
#define GLFW_INCLUDE_GLU

#include <vector>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "CameraSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
using namespace std;

class RenderSystem
{

private:

	GLFWwindow *_window;
	CameraSystem *_cameraSystem;
	vector<Entity *> *_newObjects;

	void update(vector<Entity *> *entityArray);
	void checkForNewObjects(vector<Entity *> *entityArray);
	void renderTextInformation();
	void setGunPosition(Entity* entity);
	void playAudio(Entity* entity);
	void moveToShader(Entity* entity);

	bool _firstRender; 

	RenderSystem();
	~RenderSystem();

public:

	vector<Entity *> *getNewObjects();

	void setFreshRender();

	void render(vector<Entity *> *entityArray);
	static RenderSystem& getRenderSystem();
	static void destroyRenderSystem();

};

