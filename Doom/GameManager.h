#pragma once
#include <iostream>
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "MovementSystem.h"
#include "CameraSystem.h"
#include "Scene.h"
#include "PlayerInputSystem.h"
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



	PlayerInputSystem *_playerInputSystem;


	Scene *_scene;


	GLfloat _deltaTime;

	GameManager(bool running);
	~GameManager();
	//rutututu
	void hi();

public:

	void runGameLoop();
	GLfloat getDeltaTime();
	Scene *getScene();

	static GameManager& getGameManager();
	static void destroyGameManager();
};

