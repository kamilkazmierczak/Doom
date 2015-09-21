#pragma once
#include "CameraSystem.h"
#include "Player.h"
#include "Vector3.h"
#include <GLFW/glfw3.h>

class EnvironmentReactions
{
private:

	void takeAmmo();
	void createWave();
	
	EnvironmentReactions();
	~EnvironmentReactions();

public:

	void react();

	static EnvironmentReactions& getEnvironmentReactions();
	static void destroyEnvironmentReactions();
};

