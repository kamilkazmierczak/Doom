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
	bool _pause;
	bool _restart;
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

	void hi();

public:

	void runGameLoop();
	void restartGame();

	GLfloat getDeltaTime();
	Scene *getScene();

	bool getPauseState();
	void setPauseState(bool option);

	bool getRestartState();
	void setRestartState(bool option);

	static GameManager& getGameManager();
	static void destroyGameManager();
};

