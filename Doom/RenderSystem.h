#pragma once
#include <iostream>
#define GLFW_INCLUDE_GLU //raczej zakazane bo chyba to gluLookAt

#include <vector>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "CameraSystem.h"
#include "ArtificialIntelligence.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
//#include "GameManager.h" //po wysokosc i szerokosc do raczej zakazanych funkcji
using namespace std;

class RenderSystem
{

private:

	GLFWwindow *_window;
	CameraSystem *_cameraSystem;

	//przenies to jak i cala detekcje kolizji do ModelObject
	//ArtificialIntelligence *_Ai;
	//Camera *_currentCamera;

	vector<Entity *> *_newObjects;

	void update(vector<Entity *> *entityArray);
	void checkForNewObjects(vector<Entity *> *entityArray);

	bool _firstRender;

	RenderSystem();
	~RenderSystem();

public:

	//Camera *getCurrentCamera();   // po co mi to tutaj?
	//void setCurrentCamera(Camera *newCamera); //to tez przecieza camera system wszystko ma

	vector<Entity *> *getNewObjects();

	void render(vector<Entity *> *entityArray);
	static RenderSystem& getRenderSystem();
	static void destroyRenderSystem();

};

