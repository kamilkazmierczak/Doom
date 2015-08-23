#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

class PlayerInputSystem
{
private:

	PlayerInputSystem();
	~PlayerInputSystem();

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	//void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

public:
	static PlayerInputSystem& getPlayerInputSystem();
	static void destroyPlayerInputSystem();

	static void keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mode);
	//static void mouseCallbackFun(GLFWwindow* window, double xpos, double ypos);
	//static void scrollCallbackFun(GLFWwindow* window, double xoffset, double yoffset);
};

