#pragma once
#include "CameraSystem.h"
#include "Vector3.h"
#include <GLFW/glfw3.h>

class Player
{
private:
	GLfloat _health;
	CameraSystem *_cameraSystem;
	//Vector3 _position;

	Player();
	~Player();
public:

	GLfloat getHealth();
	void changeHealth(GLfloat change);

	Vector3 getPosition();
	static Player& getPlayer();
	static void destroyPlayer();
};

