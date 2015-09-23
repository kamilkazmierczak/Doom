#pragma once
#include <iostream>
#include "Entity.h"
#include "EnvironmentReactions.h"
#include "TextRender.h"
#include "Camera.h"
#include <GLFW/glfw3.h>


class PlayerInputSystem
{
private:

	GLfloat _mouseLastX;
	GLfloat _mouseLastY;
	GLfloat _deltaTime;
	GLfloat _lastFrame;
	bool _firstMouse;

	GLfloat _lastShootTime;

	Vector3 _eyeVector;

	Camera *_currentCamera;
	//Entity *_currentPlayer;
	GLFWwindow *_window;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	PlayerInputSystem();
	~PlayerInputSystem();

public:
	void update();
	
	//void setCurrentPlayer(Entity *newPlayer);
	void setCurrentCamera(Camera *newCamera);

	static PlayerInputSystem& getPlayerInputSystem();
	static void destroyPlayerInputSystem();

	static void keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseCallbackFun(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallbackFun(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallbackFun(GLFWwindow* window, double xoffset, double yoffset);
};

