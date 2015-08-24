#pragma once
#include <iostream>
#include "Entity.h"
#include "Vector2.h"
#include <GLFW/glfw3.h>


class PlayerInputSystem
{
private:

	Vector2 _lastMousePosition;

	Vector3 _eyeVector;

	Entity *_currentPlayer;
	GLFWwindow *_window;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	//void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	PlayerInputSystem();
	~PlayerInputSystem();

public:
	void update();
	
	void setCurrentPlayer(Entity *newPlayer);


	static PlayerInputSystem& getPlayerInputSystem();
	static void destroyPlayerInputSystem();

	static void keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mode);
	//static void mouseCallbackFun(GLFWwindow* window, double xpos, double ypos);
	//static void scrollCallbackFun(GLFWwindow* window, double xoffset, double yoffset);
};

