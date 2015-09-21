#pragma once
#include "CameraSystem.h"
#include "Vector3.h"
#include <GLFW/glfw3.h>

class Player
{
private:
	GLfloat _health;
	GLfloat _ammo;
	CameraSystem *_cameraSystem;
	//Vector3 _position;

	Player();
	~Player();
public:

	GLfloat getHealth();
	void changeHealth(GLfloat change);

	GLfloat getAmmo();
	void setAmmo(GLfloat newAmmo);


	Vector3 getPosition();
	static Player& getPlayer();
	static void destroyPlayer();
};

