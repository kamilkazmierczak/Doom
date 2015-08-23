#pragma once
#include <iostream>
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "MovementSystem.h"
#include "CameraSystem.h"
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
using namespace std;
class GameManager
{

private:

	bool _running;
	RenderSystem *_renderSystem;
	ResourceManager *_resourceManager;
	MovementSystem *_movementSystem;
	CameraSystem *_cameraSystem;
	GLFWwindow *_window;

	Entity *entity; //temporary
	Entity *camera;

	GameManager(bool running);
	~GameManager();
	//rutututu
	void hi();

public:

	void runGameLoop();

	static GameManager& getGameManager();
	static void destroyGameManager();
};

